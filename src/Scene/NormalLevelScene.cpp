//
// Created by 李政翰 on 2026/4/7.
//
#include "Scene/NormalLevelScene.hpp"
#include "Manager/SceneManager.hpp"
#include "Factory/PlantFactory.hpp"
#include "Factory/ZombieFactory.hpp"

#include "Level/LevelTypes.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"

NormalLevelScene::NormalLevelScene(const LevelConfig& config, SceneManager* manager)
    : m_Manager(manager),
      m_Config(config),
      m_Board(config.rows, config.cols, config.startX, config.startY) {
}

void NormalLevelScene::on_enter() {
    LOG_DEBUG("Enter NormalLevelScene => Level {}", m_Config.levelId);

    m_LevelTimer = 0.0f;
    m_SunPoints = m_Config.initialSun;

    CreateBackground();
    CreateSeedChooserFromConfig();
    UpdateSunText();


}

void NormalLevelScene::on_update() {
    HandleInput();

    m_LevelTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;

    UpdateWaveSpawning();
    UpdatePlants();
    UpdateZombies();
    UpdateProjectiles();

    RemoveDeadProjectiles();
}

void NormalLevelScene::on_render() {
    m_Root.Update();
}

void NormalLevelScene::on_exit() {
    LOG_DEBUG("Exit NormalLevelScene => Level {}", m_Config.levelId);
}

void NormalLevelScene::CreateBackground() {
    m_Background = std::make_shared<BackgroundImage>(m_Config.backgroundPath);

    m_Objects.push_back(m_Background);
    m_Root.AddChild(m_Background);
}

void NormalLevelScene::CreateSeedChooserFromConfig() {
    m_SeedChooser = std::make_shared<SeedChooser>(SeedChooserPos);

    m_Objects.push_back(m_SeedChooser->GetBackgroundObject());
    m_Root.AddChild(m_SeedChooser->GetBackgroundObject());

    m_Objects.push_back(m_SeedChooser->GetSunText());
    m_Root.AddChild(m_SeedChooser->GetSunText());

    for (PlantType type : m_Config.allowedPlants) {
        auto card = SeedCardFactory::CreateSeedCard(type, glm::vec2(0.0f, 0.0f));

        if (card != nullptr) {
            m_SeedChooser->AddCard(card);
            m_Root.AddChild(card);
        }
    }

    m_SeedChooser->LayoutCards();
}

void NormalLevelScene::UpdateSunText() {
    m_SeedChooser->UpdateSun(m_SunPoints);
}


void NormalLevelScene::HandleInput() {
    bool isMousePressed = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);

    if (!isMousePressed && m_WasMousePressed) {
        ProcessMouseClick();
    }

    m_WasMousePressed = isMousePressed;
}

void NormalLevelScene::ProcessMouseClick() {
    glm::vec2 mousePos = Util::Input::GetCursorPosition();

    if (TrySelectSeedCard(mousePos)) {
        return;
    }

    if (!m_SeedChooser || !m_SeedChooser->HasSelection()) {
        return;
    }

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

bool NormalLevelScene::TrySelectSeedCard(const glm::vec2& mousePos) {
    if (!m_SeedChooser) {
        return false;
    }

    bool selected = m_SeedChooser->TrySelectCard(mousePos);
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

    m_Plants.push_back(plant);
    m_Board.PlacePlant(plant.get(), row, col);
    m_Root.AddChild(plant);

    m_SunPoints -= PlantFactory::GetCost(type);
    UpdateSunText();

    LOG_DEBUG("Placed plant at row={}, col={}", row, col);
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
    spawnPos.x += 380.0f;

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
    if (!plant->CanShoot()) {
        return;
    }

    auto pea = std::make_shared<Pea>(
        plant->GetRow(),
        plant->GetProjectileSpawnPosition()
    );

    SpawnProjectile(pea);
    plant->ResetShootTimer();

    LOG_DEBUG("Plant fired projectile");
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
void NormalLevelScene::RemoveDeadProjectiles() {
    m_Projectiles.erase(
        std::remove_if(
            m_Projectiles.begin(),
            m_Projectiles.end(),
            [](const std::shared_ptr<Projectile>& projectile) {
                return !projectile || !projectile->IsAlive();
            }
        ),
        m_Projectiles.end()
    );
}


