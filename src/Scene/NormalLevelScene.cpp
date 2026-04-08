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
    CreateSeedChooserFromConfig();
    UpdateSunText();
}

void NormalLevelScene::on_update() {
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