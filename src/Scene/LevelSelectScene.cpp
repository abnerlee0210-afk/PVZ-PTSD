//
// Created by 李政翰 on 2026/4/1.
//
#include "Scene/LevelSelectScene.hpp"
#include "Manager/SceneManager.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

LevelSelectScene::LevelSelectScene(SceneManager* manager) : m_Manager(manager){
    LOG_DEBUG("MenuScene Constructor");
}

LevelSelectScene::~LevelSelectScene() {
    LOG_DEBUG("MenuScene Destructor");
}


void LevelSelectScene::on_enter() {
    m_Background = std::make_shared<BackgroundImage>();
    m_Background->Set_Background(BackgroundImagePath);

    m_PlayButton = std::make_shared<Button>(PlayButtonImage,PlayButtonPos);
    m_BackButton = std::make_shared<Button>(BackButtonImage, BackButtonPos);

    for (int i = 0; i < 10; ++i) {
        auto card = std::make_shared<LevelCard>(
            i + 1,
            LevelCardImage + std::to_string(i+1) + ".png",
            glm::vec2(0.0f, m_CardY)
        );

        m_LevelCards.push_back(card);
        m_Root.AddChild(card->GetImageObject());
        // m_Root.AddChild(card->GetTextObject());
    }

    // 問題：Update 每秒執行 60 次，你就設定了 60 次 Callback。這會造成不必要的記憶體分配。
    // 修正：把 SetCallback 移到 on_enter()。
    m_PlayButton->SetCallback([this]() {
        LOG_DEBUG("PlayButton pressed, switching to Game{}", m_SelectedIndex + 1);
        if (m_Manager) {
            m_Manager->switch_to(SceneManager::SceneType::NORMALGAME,m_SelectedIndex + 1);
        }
    });
    m_BackButton->SetCallback([this]() {
        LOG_DEBUG("BackButton pressed, switching to MenuScene");
        if (m_Manager) {
            m_Manager->switch_to(SceneManager::SceneType::MENU);
        }
    });

    m_Root.AddChild(m_Background);
    m_Root.AddChild(m_PlayButton);
    m_Root.AddChild(m_BackButton);
}

void LevelSelectScene::on_update() {
    HandleInput();

    // 平滑移動
    float diff = m_TargetScrollOffset - m_CurrentScrollOffset;
    m_CurrentScrollOffset += diff * 0.12f;

    UpdateCardPositions();
    UpdateSelectionVisual();
}

void LevelSelectScene::on_render() {
    m_Root.Update();
}

void LevelSelectScene::on_exit() {
    LOG_DEBUG("Exiting MenuScene");
    m_Root.RemoveChild(m_Background);
    m_Root.RemoveChild(m_PlayButton);
    m_Root.RemoveChild( m_BackButton);
    for (auto& L : m_LevelCards) {
        m_Root.RemoveChild((L->GetImageObject()));
    }
    m_LevelCards.clear(); // 清空 vector
}


void LevelSelectScene::HandleInput() {
    // 處理鍵盤左右鍵切換關卡
    if (Util::Input::IsKeyDown(Util::Keycode::RIGHT)) {
        if (m_SelectedIndex < static_cast<int>(m_LevelCards.size()) - 1) {
            ++m_SelectedIndex;
            m_TargetScrollOffset = -m_SelectedIndex * m_CardSpacing;
            LOG_DEBUG("Select level => {}", m_SelectedIndex + 1);
        }
    }

    if (Util::Input::IsKeyDown(Util::Keycode::LEFT)) {
        if (m_SelectedIndex > 0) {
            --m_SelectedIndex;
            m_TargetScrollOffset = -m_SelectedIndex * m_CardSpacing;
            LOG_DEBUG("Select level => {}", m_SelectedIndex + 1);
        }
    }

    // 處理 PlayButton 進入指定遊戲關卡
    m_PlayButton->Update();
    if (m_PlayButton->IsMouseHovering()) {
        m_PlayButton->SetImage(PlayButtonFeedback);
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            LOG_DEBUG("Play level => {}", GetSelectedLevel());
            m_PlayButton->SetVisualScaleFactor(1.2f);
            // 之後這裡接進 App 的切場景邏輯
        }
        else {m_PlayButton->SetVisualScaleFactor(1.0f);}
    }
    else {m_PlayButton->SetImage(PlayButtonImage);}

    // 處理 BackButton 返回 MenuScene
    m_BackButton->Update();
    if (m_BackButton->IsMouseHovering()) {
        m_BackButton->SetImage(BackButtonFeedback);
        if (Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB)) {
            LOG_DEBUG("Back to Menu");
            m_BackButton->SetVisualScaleFactor(1.2f);
            // 之後這裡接進 App 的切場景邏輯
        }
        else {m_BackButton->SetVisualScaleFactor(1.0f);}
    }
    else {m_BackButton->SetImage(BackButtonImage);}
}


void LevelSelectScene::UpdateCardPositions() {
    for (int i = 0; i < static_cast<int>(m_LevelCards.size()); ++i) {
        float x = m_CenterX + i * m_CardSpacing + m_CurrentScrollOffset;
        m_LevelCards[i]->SetPosition({x, m_CardY});
    }
}

void LevelSelectScene::UpdateSelectionVisual() {
    for (int i = 0; i < static_cast<int>(m_LevelCards.size()); ++i) {
        m_LevelCards[i]->SetSelected(i == m_SelectedIndex);
    }
}

int LevelSelectScene::GetSelectedLevel() const {
    return m_SelectedIndex + 1;
}