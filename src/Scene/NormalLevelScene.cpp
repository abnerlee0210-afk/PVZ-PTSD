//
// Created by 李政翰 on 2026/4/7.
//
#include "Scene/NormalLevelScene.hpp"
#include "Manager/SceneManager.hpp"

#include "Level/LevelTypes.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"

NormalLevelScene::NormalLevelScene(const LevelConfig& config, SceneManager* manager)
    : m_Manager(manager),
      m_Config(config),
      m_Board(config.rows, config.cols, config.startX, config.startY) {
}

void NormalLevelScene::on_enter() {
    LOG_DEBUG("Enter NormalLevelScene => Level {}", m_Config.levelId);

    m_SunPoints = m_Config.initialSun;

    CreateBackground();
    CreateSunText();
    CreateSeedCardsFromConfig();
    UpdateSunText();
}

void NormalLevelScene::on_update() {
    // 第一版先不做戰鬥邏輯
    // 之後再加 HandleInput / Wave / Zombie / Sun
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

void NormalLevelScene::CreateSunText() {
    m_SunText = std::make_shared<Text>("0",20.0f);
    m_SunText->m_Transform.translation = {-510.0f, 230.0f};

    m_Objects.push_back(m_SunText);
    m_Root.AddChild(m_SunText);
}

void NormalLevelScene::CreateSeedCardsFromConfig() {
    float startX = -455.0f;
    float y = 262.0f;
    float spacing = 55.0f;

    for (int i = 0; i < static_cast<int>(m_Config.allowedPlants.size()); ++i) {
        PlantType type = m_Config.allowedPlants[i];

        auto card = SeedCardFactory::CreateSeedCard(
            type,
            glm::vec2(startX + i * spacing, y)
        );

        if (card != nullptr) {
            m_SeedCards.push_back(card);
            m_Root.AddChild(card);
        }
    }

    if (!m_SeedCards.empty()) {
        m_SeedCards[0]->SetSelected(true);
    }
}

void NormalLevelScene::UpdateSunText() {
    if (m_SunText != nullptr) {
        m_SunText->SetText(std::to_string(m_SunPoints));
    }
}