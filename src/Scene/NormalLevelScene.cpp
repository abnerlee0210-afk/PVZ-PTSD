//
// Created by 李政翰 on 2026/4/7.
//
#include "Scene/NormalLevelScene.hpp"
#include "Manager/SceneManager.hpp"
#include "Board/BoardPresets.hpp"
#include "Factory/PlantFactory.hpp"
#include "Factory/ZombieFactory.hpp"

#include "Level/LevelTypes.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"

#include "Entity/Peashooter.hpp"
#include "Entity/Sunflower.hpp"
#include "Entity/BasicZombie.hpp"
#include "Entity/Pea.hpp"

NormalLevelScene::NormalLevelScene(const LevelConfig& config, SceneManager* manager)
    : m_Manager(manager),
      m_Config(config),
      m_Board(config.rows, config.cols, BoardPresets::GetLayout(config.boardTypes)) {
}

void NormalLevelScene::on_enter() {
    LOG_DEBUG("Enter NormalLevelScene => Level {}", m_Config.levelId);

    m_GameState = GameState::PLAYING;
    m_LevelTimer = 0.0f;
    m_SkySunTimer = 0.0f;

    m_NextSkySunInterval = m_Config.skySunMinInterval;
    m_SunPoints = m_Config.initialSun;

    CreateBackground();
    CreateLawnMowersFromConfig();
    CreateSeedChooserFromConfig();
    UpdateSunText();

}

void NormalLevelScene::on_update() {
    if (m_GameState == GameState::VICTORY || m_GameState == GameState::GAME_OVER) {
        HanldeEndScreenInput();
        return;
    }
    if (m_GameState!=GameState::PLAYING) {return;}

    HandleInput();

    float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_LevelTimer += deltaTime;

    UpdateSkySunSystem(deltaTime);

    // Update
    UpdateSeedCards();
    UpdateWaveSpawning();
    UpdatePlants();
    UpdateZombies();
    UpdateLawnMowers();
    UpdateProjectiles();
    UpdateSuns();


    // 偵測碰撞
    CheckZombieLawnMowerCollisions();
    CheckProjectileZombieCollisions();
    CheckZombiePlantCollisions();

    // 移除死亡物件
    RemoveDeadEntities();

    CheckGameOver();
    CheckVictory();
}

void NormalLevelScene::on_render() {
    m_Root.Update();
}

void NormalLevelScene::on_exit() {
    LOG_DEBUG("Exit NormalLevelScene => Level {}", m_Config.levelId);

    RemoveAllEntity();

    if (m_VictoryScreen) {
        m_Root.RemoveChild(m_VictoryScreen);
        m_VictoryScreen = nullptr;
    }

    if (m_Background) {
        m_Root.RemoveChild(m_Background);
        m_Background = nullptr;
    }

    if (m_SeedChooser) {
        if (m_SeedChooser->GetBackgroundObject()) {
            m_Root.RemoveChild(m_SeedChooser->GetBackgroundObject());
        }
        if (m_SeedChooser->GetSunText()) {
            m_Root.RemoveChild(m_SeedChooser->GetSunText());
        }
        for (auto& card : m_SeedChooser->GetCards()) {
            if (card) {
                m_Root.RemoveChild(card);
                if (card->GetCooldownOverlay()) {
                    m_Root.RemoveChild(card->GetCooldownOverlay());
                }
                if (card->GetOuterFrame()) {
                    m_Root.RemoveChild(card->GetOuterFrame());
                }
                if (card->GetCooldownText()) {
                    m_Root.RemoveChild(card->GetCooldownText());
                }
            }
        }
        m_SeedChooser = nullptr;
    }
}

// ==================================================
// Create / 初始化
// ==================================================
void NormalLevelScene::CreateBackground() {
    m_Background = std::make_shared<BackgroundImage>(m_Config.backgroundPath);
    m_Background->m_Transform.translation = m_Config.BackgroundPos;

    m_Objects.push_back(m_Background);
    m_Root.AddChild(m_Background);
}
void NormalLevelScene::CreateLawnMowersFromConfig() {
    if (!m_Config.hasLawnMowers) {
        return;
    }

    for (int row : m_Config.lawnMowerRows) {
        glm::vec2 pos = m_Board.GetCellCenter(row, 0);

        // 放在第 0 欄再往左一點
        pos.x = m_Config.m_HomeLineX + 1.0f;

        auto mower = std::make_shared<LawnMower>(row, pos);
        m_LawnMowers.push_back(mower);
        m_Root.AddChild(mower);
    }
}
void NormalLevelScene::CreateSeedChooserFromConfig() {
    m_SeedChooser = std::make_shared<SeedChooser>(m_Config.SeedChooserPos);

    m_Objects.push_back(m_SeedChooser->GetBackgroundObject());
    m_Root.AddChild(m_SeedChooser->GetBackgroundObject());

    m_Objects.push_back(m_SeedChooser->GetSunText());
    m_Root.AddChild(m_SeedChooser->GetSunText());

    for (PlantType type : m_Config.allowedPlants) {
        auto card = SeedCardFactory::CreateSeedCard(type, glm::vec2(0.0f, 0.0f));

        if (card != nullptr) {
            m_SeedChooser->AddCard(card);
            m_Root.AddChild(card);
            if (card->GetCooldownOverlay()) {
                m_Root.AddChild(card->GetCooldownOverlay());
            }
            if (card->GetCooldownText()) {
                m_Root.AddChild(card->GetCooldownText());
            }
            if (card->GetOuterFrame()) {
                m_Root.AddChild(card->GetOuterFrame());
            }
        }
    }

    m_SeedChooser->LayoutCards();
}

void NormalLevelScene::UpdateSunText() {
    m_SeedChooser->UpdateSun(m_SunPoints);
}

// ==================================================
// 處理iuput
// ==================================================
void NormalLevelScene::HandleInput() {
    bool isMousePressed = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);

    if (!isMousePressed && m_WasMousePressed) {
        ProcessMouseClick();
    }

    m_WasMousePressed = isMousePressed;
}
void NormalLevelScene::ProcessMouseClick() {
    glm::vec2 mousePos = Util::Input::GetCursorPosition();
    LOG_DEBUG("X:{},Y:{}",mousePos.x, mousePos.y);

    if (TrySelectSeedCard(mousePos)) {
        return;
    }

    //
    if (TryCollectSun(mousePos)) {
        return;
    }
    //

    if (!m_SeedChooser || !m_SeedChooser->HasSelection()) {
        return;
    }

    auto selectedCard = m_SeedChooser->GetSelectedCard();
    if (!selectedCard) { return;}
    if (!selectedCard->IsUsable(m_SunPoints,m_LevelTimer)) {return;}

    int row = 0;
    int col = 0;
    if (!m_Board.ScreenToGrid(mousePos.x, mousePos.y, row, col)) {
        return;
    }

    PlantType selectedType = m_SeedChooser->GetSelectedPlantType();

    if (!CanPlantAt(row, col, selectedType)) {
        return;
    }

    PlacePlantAt(row, col, selectedType);
}

// ==================================================
// 選卡 / 種植
// ==================================================
bool NormalLevelScene::TrySelectSeedCard(const glm::vec2& mousePos) {
    if (!m_SeedChooser) {
        return false;
    }

    bool selected = m_SeedChooser->TrySelectCard(mousePos, m_SunPoints, m_LevelTimer);
    if (selected) {
        LOG_DEBUG("Seed card selected");
    }
    return selected;
}
bool NormalLevelScene::CanPlantAt(int row, int col, PlantType type) const {
    if (!m_Board.IsCellEmpty(row, col)) {
        LOG_DEBUG("Cell already occupied: row={}, col={}", row, col);
        return false;
    }

    int cost = PlantFactory::GetCost(type);
    if (m_SunPoints < cost) {
        LOG_DEBUG("Not enough sun");
        return false;
    }

    return true;
}
void NormalLevelScene::PlacePlantAt(int row, int col, PlantType type) {
    glm::vec2 plantPos = m_Board.GetCellCenter(row, col);

    auto plant = PlantFactory::CreatePlant(type, row, col, plantPos);
    if (!plant) {
        LOG_DEBUG("Failed to create plant");
        return;
    }

    auto selectedCard = m_SeedChooser->GetSelectedCard();
    if (selectedCard) {
        selectedCard->TriggerCooldown(m_LevelTimer);
    }

    m_Plants.push_back(plant);
    m_Board.PlacePlant(plant.get(), row, col);
    m_Root.AddChild(plant);

    m_SunPoints -= PlantFactory::GetCost(type);
    UpdateSunText();

    LOG_DEBUG("Placed plant at row={}, col={}", row, col);
}
void NormalLevelScene::UpdateSeedCards() {
    if (!m_SeedChooser) { return; }
    for (auto& card: m_SeedChooser->GetCards()) {
        if (card) {
            card->UpdateVisualState(m_SunPoints, m_LevelTimer);
        }
    }
}




// ==================================================
// Zombie生成及Update
// ==================================================
void NormalLevelScene::UpdateWaveSpawning() {
    for (auto& wave : m_Config.waves) {
        for (auto& event : wave.events) {
            if (!event.spawned && m_LevelTimer >= event.spawnTime) {
                SpawnZombiesFromEvent(event);
                event.spawned = true;
            }
        }
    }
}
void NormalLevelScene::SpawnZombiesFromEvent(const SpawnEvent &event) {
    SpawnZombieByType(event.type, event.row);
}
void NormalLevelScene::SpawnZombieByType(ZombieType type, int row) {
    glm::vec2 spawnPos = m_Board.GetCellCenter(row, m_Config.cols-1);
    spawnPos.x += m_Config.SpawnZombiePosXBias;

    auto zombie = ZombieFactory::CreateZombie(type,row, spawnPos);
    if (!zombie) {
        LOG_DEBUG("Failed to create zombie");
        return;
    }

    m_Zombies.push_back(zombie);
    m_Root.AddChild(zombie);

    LOG_DEBUG("Spawned zombie => row={}, x={}, y={}", row, spawnPos.x, spawnPos.y);
}
void NormalLevelScene::UpdateZombies() {
    for (auto& zombie : m_Zombies) {
        if (zombie && zombie->IsAlive()) {
            zombie->Update();
        }
    }
}


// ==================================================
// 更新植物 UpdatePlants、UpdateSinglePlant
// ==================================================
void NormalLevelScene::UpdatePlants() {
    for (auto& plant : m_Plants) {
        if (!plant || !plant->IsAlive()) {
            continue;
        }

        UpdateSinglePlant(plant); // 個別處裡
    }
}
void NormalLevelScene::UpdateSinglePlant(const std::shared_ptr<Plant>& plant) {
    plant->Update();

    TryHandlePlantShooting(plant); // 射擊處理
}
void NormalLevelScene::TryHandlePlantShooting(const std::shared_ptr<Plant>& plant) {
    if (IsZombieInRow(plant) && plant->CanShoot()) {
        auto pea = std::make_shared<Pea>(
            plant->GetRow(),
            plant->GetProjectileSpawnPosition()
        );
        SpawnProjectile(pea);
        plant->ResetShootTimer();

        LOG_DEBUG("Plant fired projectile");
    }
}
bool NormalLevelScene::IsZombieInRow(const std::shared_ptr<Plant>& plant) const {
    if (!plant || !plant->IsAlive()) {
        return false;
    }

    for (const auto& zombie : m_Zombies) {
        if (!zombie || !zombie->IsAlive()) {
            continue;
        }

        if (zombie->GetRow() != plant->GetRow()) {
            continue;
        }

        if (zombie->m_Transform.translation.x > plant->m_Transform.translation.x ||
            zombie->m_Transform.translation.x < m_Config.boundariesX) {
            return true;
        }
    }

    return false;
}

// ==================================================
// 處理子彈部分
// ==================================================
void NormalLevelScene::SpawnProjectile(const std::shared_ptr<Projectile> &projectile) {
    if (!projectile) {return;}

    m_Projectiles.push_back(projectile);
    m_Root.AddChild(projectile);
}
void NormalLevelScene::UpdateProjectiles() {
    for (auto& projectile : m_Projectiles) {
        if (!projectile || !projectile->IsAlive()) {
            continue;
        }

        projectile->Update();
    }
}

// ==================================================
// 處理子彈和僵屍的碰撞(碰撞後移除子彈，殭屍扣血)
// ==================================================
void NormalLevelScene::CheckProjectileZombieCollisions() {
    for (auto& projectile : m_Projectiles) {
        if (!projectile || !projectile->IsAlive()) {
            continue;
        }

        for (auto& zombie : m_Zombies) {
            if (!zombie || !zombie->IsAlive()) {
                continue;
            }

            if (projectile->GetRow() != zombie->GetRow()) {
                continue;
            }

            float dx = std::abs(
                projectile->m_Transform.translation.x -
                zombie->m_Transform.translation.x
            );

            if (dx < 30.0f) {
                zombie->TakeDamage(projectile->GetDamage());
                projectile->Destroy();

                LOG_DEBUG(
                    "Projectile hit zombie => damage={}, zombieHP={}",
                    projectile->GetDamage(),
                    zombie->GetHP()
                );

                break;
            }
        }
    }
}


// ==================================================
// 處理植物和僵屍的碰撞(殭屍攻擊、植物扣血)
// ==================================================
void NormalLevelScene::CheckZombiePlantCollisions() {
    for (auto& zombie : m_Zombies) {
        if (!zombie || !zombie->IsAlive()) {
            continue;
        }

        bool foundPlantToAttack = false;

        for (auto& plant : m_Plants) {
            if (!plant || !plant->IsAlive()) {
                continue;
            }

            if (plant->GetRow() != zombie->GetRow()) {
                continue;
            }

            float dx = std::abs(
                zombie->m_Transform.translation.x -
                plant->m_Transform.translation.x
            );

            if (dx > 0 && dx < 45.0f) {
                foundPlantToAttack = true;
                zombie->SetAttacking(true);

                if (zombie->CanAttack()) {
                    plant->TakeDamage(20);
                    zombie->ResetAttackTimer();

                    LOG_DEBUG(
                        "Zombie attacked plant => plantHP={}",
                        plant->GetHP()
                    );
                }

                break;
            }
        }

        if (!foundPlantToAttack) {
            zombie->SetAttacking(false);
        }
    }
}


// ==================================================
// 處理Sun
// ==================================================
void NormalLevelScene::SpawnSun(const std::shared_ptr<Sun>& sun) {
    if (!sun) {
        return;
    }

    m_Suns.push_back(sun);
    m_Root.AddChild(sun);
}
void NormalLevelScene::SpawnSkySun() {
    float minX = static_cast<float>(m_Config.startX + 40.0f);
    float maxX = static_cast<float>(m_Config.startX + m_Config.cols * 80.0f);
    float minY = -250.0f;
    float maxY = 150.0f;

    // 建立分布器 (直接指定範圍)
    std::uniform_real_distribution<float> distX(minX, maxX);
    std::uniform_real_distribution<float> distY(minY, maxY);

    // 直接生成隨機座標
    float x = distX(m_Rng);
    float y = distY(m_Rng);

    glm::vec2 startPos = {x, 250};
    glm::vec2 targetPos = {x, y};

    auto sun = std::make_shared<Sun>(
        startPos,
        targetPos,
        25,
        m_Config.sunLifeTime
    );

    SpawnSun(sun);

    LOG_DEBUG("Spawned sky sun");
}

void NormalLevelScene::UpdateSuns() {
    for (auto& sun : m_Suns) {
        if (sun && sun->IsAlive()) {
            sun->Update();
        }
    }
}
bool NormalLevelScene::TryCollectSun(const glm::vec2& mousePos) {
    for (auto& sun : m_Suns) {
        if (!sun || !sun->IsAlive()) {
            continue;
        }

        if (sun->ContainsPoint(mousePos)) {
            m_SunPoints += sun->GetValue();
            sun->Collect();
            UpdateSunText();

            LOG_DEBUG("Collected sun, sun points = {}", m_SunPoints);
            return true;
        }
    }

    return false;
}
void NormalLevelScene::UpdateSkySunSystem(float deltaTime) {
    if (!m_Config.hasSkySun) return;

    m_SkySunTimer += deltaTime;
    if (m_SkySunTimer >= m_NextSkySunInterval) {
        SpawnSkySun();
        m_SkySunTimer = 0.0f;

        std::uniform_real_distribution<float> dist(m_Config.skySunMinInterval, m_Config.skySunMaxInterval);
        m_NextSkySunInterval = dist(m_Rng);
    }
}


// ==================================================
// 勝敗相關函式
// ==================================================
bool NormalLevelScene::AreAllWavesFinished() const {
    for (const auto& wave : m_Config.waves) {
        for (const auto& event : wave.events) {
            if (!event.spawned) {
                return false;
            }
        }
    }
    return true;
}
bool NormalLevelScene::AreAllZombiesCleared() const {
    for (const auto& zombie : m_Zombies) {
        if (zombie && zombie->IsAlive()) {
            return false;
        }
    }
    return true;
}
void NormalLevelScene::CheckVictory() {
    if (m_GameState != GameState::PLAYING) {
        return;
    }

    if (AreAllWavesFinished() && AreAllZombiesCleared()) {
        EnterVictory();
    }
}
void NormalLevelScene::CheckGameOver() {
    if (m_GameState != GameState::PLAYING) {
        return;
    }

    for (const auto& zombie : m_Zombies) {
        if (!zombie || !zombie->IsAlive()) {
            continue;
        }

        if (zombie->m_Transform.translation.x < m_Config.m_HomeLineX) {
            EnterGameOver();
            return;
        }
    }
}
void NormalLevelScene::EnterVictory() {
    if (m_GameState != GameState::PLAYING) {
        return;
    }

    m_GameState = GameState::VICTORY;
    RemoveAllEntity();
    ShowVictoryScreen();
    LOG_DEBUG("VICTORY!");
}
void NormalLevelScene::EnterGameOver() {
    if (m_GameState != GameState::PLAYING) {
        return;
    }

    m_GameState = GameState::GAME_OVER;
    RemoveAllEntity();
    ShowGameOverScreen();
    LOG_DEBUG("GAME OVER!");
}
void NormalLevelScene::ShowVictoryScreen() {
    if (m_VictoryScreen) {
        return;
    }

    LOG_DEBUG("Victory screen path = {}", m_Config.VictoryScreenPath);

    auto image = std::make_shared<Util::Image>(m_Config.VictoryScreenPath);
    m_VictoryScreen = std::make_shared<Util::GameObject>(
        image,
        1.0f
    );

    m_VictoryScreen->m_Transform.translation = {0.0f, 0.0f};

    m_Root.AddChild(m_VictoryScreen);

    LOG_DEBUG("Victory screen created");
}

void NormalLevelScene::ShowGameOverScreen() {
    if (m_GameOverScreen) {
        return;
    }

    m_GameOverScreen = std::make_shared<Util::GameObject>(
        std::make_shared<Util::Image>(
            m_Config.LooseScreenPath
        ),
        1.0f
    );

    m_GameOverScreen->m_Transform.translation = {0.0f, 0.0f};

    m_Root.AddChild(m_GameOverScreen);
}
void NormalLevelScene::HanldeEndScreenInput() {
    if (!m_Manager) {
        return;
    }

    if (Util::Input::IsKeyUp(Util::Keycode::RETURN) ||
        Util::Input::IsKeyUp(Util::Keycode::MOUSE_LB)) {
        m_Manager->switch_to(SceneManager::SceneType::MENU);
        }
}


// ==================================================
// 除草機
// ==================================================
void NormalLevelScene::UpdateLawnMowers() {
    for (auto& mower : m_LawnMowers) {
        if (mower && mower->IsAlive()) {
            mower->Update();
        }
    }
}
void NormalLevelScene::CheckZombieLawnMowerCollisions() {
    for (auto& mower : m_LawnMowers) {
        if (!mower || !mower->IsAlive()) {
            continue;
        }

        for (auto& zombie : m_Zombies) {
            if (!zombie || !zombie->IsAlive()) {
                continue;
            }

            if (mower->GetRow() != zombie->GetRow()) {
                continue;
            }

            float dx = std::abs(
                mower->m_Transform.translation.x -
                zombie->m_Transform.translation.x
            );

            // 先用一個簡單啟動距離
            if (!mower->IsActive() && dx < 40.0f) {
                mower->Activate();
            }

            // 啟動後持續撞死同列殭屍
            if (mower->IsActive() && dx < 45.0f) {
                zombie->TakeDamage(99999);
            }
        }
    }
}

// ==================================================
// Remove
// ==================================================
void NormalLevelScene::RemoveAllEntity() {
    // 移除 Plants
    for (auto& plant : m_Plants) {
        if (plant) {
            m_Root.RemoveChild(plant);
        }
    }
    m_Plants.clear();

    // 移除 Zombies
    for (auto& zombie : m_Zombies) {
        if (zombie) {
            m_Root.RemoveChild(zombie);
        }
    }
    m_Zombies.clear();

    // 移除 Projectiles
    for (auto& projectile : m_Projectiles) {
        if (projectile) {
            m_Root.RemoveChild(projectile);
        }
    }
    m_Projectiles.clear();

    // 移除 Suns
    for (auto& sun : m_Suns) {
        if (sun) {
            m_Root.RemoveChild(sun);
        }
    }
    m_Suns.clear();

    // 移除 除草機
    for (auto& LawnMower : m_LawnMowers) {
        if (LawnMower) {
            m_Root.RemoveChild(LawnMower);
        }
    }
    m_LawnMowers.clear();
}
void NormalLevelScene::RemoveDeadEntities() {
    // 移除子彈
    for (auto it = m_Projectiles.begin(); it != m_Projectiles.end(); ) {
        if (!(*it) || !(*it)->IsAlive()) {
            m_Root.RemoveChild(*it);
            it = m_Projectiles.erase(it);
        } else {
            ++it;
        }
    }

    // 移除死亡的殭屍
    for (auto it = m_Zombies.begin(); it != m_Zombies.end(); ) {
        if (!(*it) || !(*it)->IsAlive()) {
            m_Root.RemoveChild(*it); // 1️⃣ 從 Renderer 移除
            it = m_Zombies.erase(it); // 2️⃣ 從 vector 移除
        } else {
            ++it;
        }
    }

    // 移除死亡的植物
    for (auto it = m_Plants.begin(); it != m_Plants.end(); ) {
        if (!(*it) || !(*it)->IsAlive()) {
            if (*it) {
                m_Board.RemovePlant((*it)->GetRow(), (*it)->GetCol());
                m_Root.RemoveChild(*it);
            }
            it = m_Plants.erase(it);
        } else {
            ++it;
        }
    }

    // 移除陽光
    for (auto it = m_Suns.begin(); it != m_Suns.end(); ) {
        if (!(*it) || !(*it)->IsAlive()) {
            if (*it) {
                m_Root.RemoveChild(*it);
            }
            it = m_Suns.erase(it);
        } else {
            ++it;
        }
    }

    // 移除除草機
    for (auto it = m_LawnMowers.begin(); it != m_LawnMowers.end(); ) {
        if (!(*it) || !(*it)->IsAlive()) {
            if (*it) {
                m_Root.RemoveChild(*it);
            }
            it = m_LawnMowers.erase(it);
        } else {
            ++it;
        }
    }

}
