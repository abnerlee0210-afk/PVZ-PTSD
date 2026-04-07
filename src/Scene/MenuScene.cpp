//
// Created by 李政翰 on 2026/3/31.
//
#include "Scene/MenuScene.hpp"
#include "../../include/Manager/SceneManager.hpp"

MenuScene::MenuScene(SceneManager* manager) : m_Manager(manager) {
    LOG_DEBUG("MenuScene Constructor with Manager");
}

MenuScene::~MenuScene() {
    LOG_DEBUG("MenuScene Destructor");
}

void MenuScene::on_enter() {
    LOG_DEBUG("Entering MenuScene");

    m_Background = std::make_shared<BackgroundImage>();
    m_Background->Set_Background(BackgroundImagePath);

    m_PlayButton = std::make_shared<Button>(PlayButtonNormal, glm::vec2(270, 180));

    m_PlayButton->SetCallback([this]() {
        LOG_DEBUG("Button pressed, switching to SelectScene");
        // 使用儲存好的 m_Manager 進行切換
        if (m_Manager) {
            m_Manager->switch_to(SceneManager::SceneType::SELECT);
        }
    });

    m_Root.AddChild(m_Background);
    m_Root.AddChild(m_PlayButton);
}

void MenuScene::on_update() {
    // Button
    m_PlayButton->Update();

    // Button懸停效果（鼠標在範圍內Button變暗，點擊後縮放）
    if (m_PlayButton->IsMouseHovering()) {
        m_PlayButton->SetImage(PlayButtonFeedback);
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {m_PlayButton->SetVisualScaleFactor(1.2f);}
        else {m_PlayButton->SetVisualScaleFactor(1.0f);}
    }
    else {m_PlayButton->SetImage(PlayButtonNormal);}
}

void MenuScene::on_render() {
    m_Root.Update();
}

void MenuScene::on_exit() {
    LOG_DEBUG("Exiting MenuScene");
    m_Root.RemoveChild(m_Background);
    m_Root.RemoveChild(m_PlayButton);
}
