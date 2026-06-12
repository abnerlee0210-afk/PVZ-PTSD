//
// Created by 李政翰 on 2026/4/7.
//
#include "Scene/BowlingLevelScene.hpp"

#include "Manager/SceneManager.hpp"
#include "Factory/ZombieFactory.hpp"
#include "Board/BoardPresets.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Time.hpp"
#include "Util/Logger.hpp"

BowlingLevelScene::BowlingLevelScene(const LevelConfig& config, SceneManager* manager)
    : m_Manager(manager),
      m_Config(config),
      m_Board(config.rows, config.cols, BoardPresets::GetLayout(config.boardTypes)) {
}

void BowlingLevelScene::SetLevelConfig(const LevelConfig& config) {
    m_Config = config;
    m_Board = GameBoard(
        m_Config.rows,
        m_Config.cols,
        BoardPresets::GetLayout(m_Config.boardTypes)
    );
}

void BowlingLevelScene::on_enter() {
    LOG_DEBUG("Enter BowlingLevelScene => Level {}", m_Config.levelId);

    m_LevelTimer = 0.0f;
    m_WasMousePressed = false;

    CreateBackground();
}

void BowlingLevelScene::on_update() {
    float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;
    m_LevelTimer += deltaTime;

    HandleInput();

    UpdateWaveSpawning();
    UpdateZombies();
    UpdateBowlingNuts();
}

void BowlingLevelScene::on_render() {
    m_Root.Update();
}

void BowlingLevelScene::on_exit() {
    if (m_Background) {
        m_Root.RemoveChild(m_Background);
        m_Background = nullptr;
    }

    for (auto& zombie : m_Zombies) {
        if (zombie) {
            m_Root.RemoveChild(zombie);
        }
    }
    m_Zombies.clear();
}

void BowlingLevelScene::CreateBackground() {
    m_Background = std::make_shared<BackgroundImage>(m_Config.backgroundPath);
    m_Background->m_Transform.translation = m_Config.BackgroundPos;
    m_Root.AddChild(m_Background);
}

void BowlingLevelScene::HandleInput() {
    // 下一步接：點某一列發射 BowlingNut
}

void BowlingLevelScene::UpdateZombies() {
    for (auto& zombie : m_Zombies) {
        if (zombie && !zombie->ShouldRemove()) {
            zombie->Update();
        }
    }
}

void BowlingLevelScene::UpdateBowlingNuts() {
    // 下一步接 BowlingNut
}

void BowlingLevelScene::UpdateWaveSpawning() {
    for (auto& wave : m_Config.waves) {
        for (auto& event : wave.events) {
            if (!event.spawned && m_LevelTimer >= event.spawnTime) {
                SpawnZombiesFromEvent(event);
                event.spawned = true;
            }
        }
    }
}

void BowlingLevelScene::SpawnZombiesFromEvent(const SpawnEvent& event) {
    SpawnZombieByType(event.type, event.row);
}

void BowlingLevelScene::SpawnZombieByType(ZombieType type, int row) {
    if (row < 0) {
        row = rand() % m_Config.rows; // 之後可換成 mt19937
    }

    glm::vec2 spawnPos = m_Board.GetCellCenter(row, m_Config.cols - 1);
    spawnPos.x += m_Config.SpawnZombiePosXBias;

    auto zombie = ZombieFactory::CreateZombie(type, row, spawnPos);

    if (!zombie) {
        return;
    }

    m_Zombies.push_back(zombie);
    m_Root.AddChild(zombie);
}