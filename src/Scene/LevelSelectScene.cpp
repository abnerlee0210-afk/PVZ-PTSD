//
// Created by 李政翰 on 2026/4/1.
//
#include "Scene/LevelSelectScene.hpp"

#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"
#include "Util/Time.hpp"

LevelSelectScene::LevelSelectScene() {
    auto bgImage = std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Screen/select_bg.png");
    m_Background = std::make_shared<Util::GameObject>(bgImage, 0.0f);
    m_Background->m_Transform.translation = {0.0f, 0.0f};
    m_Renderer.AddChild(m_Background);

    auto playImage = std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Screen/play_button.png");
    m_PlayButton = std::make_shared<Util::GameObject>(playImage, 30.0f);
    m_PlayButton->m_Transform.translation = {680.0f, 520.0f};
    m_Renderer.AddChild(m_PlayButton);

    for (int i = 0; i < 10; ++i) {
        auto card = std::make_shared<LevelCard>(
            i + 1,
            RESOURCE_DIR "/graphics/Screen/level_card.png",
            glm::vec2(0.0f, m_CardY),
            true
        );

        m_LevelCards.push_back(card);
        m_Renderer.AddChild(card->GetImageObject());
        m_Renderer.AddChild(card->GetTextObject());
    }

    UpdateCardPositions();
    UpdateSelectionVisual();
}

void LevelSelectScene::Update() {
    HandleInput();

    // 平滑移動
    float diff = m_TargetScrollOffset - m_CurrentScrollOffset;
    m_CurrentScrollOffset += diff * 0.12f;

    UpdateCardPositions();
    UpdateSelectionVisual();

    m_Renderer.Update();
}

void LevelSelectScene::HandleInput() {
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

    const bool isMousePressed = Util::Input::IsKeyDown(Util::Keycode::MOUSE_LB);

    if (isMousePressed && !m_WasMousePressed) {
        const glm::vec2 mousePos = Util::Input::GetCursorPosition();

        TrySelectCardByMouse();

        if (IsPlayButtonClicked(mousePos)) {
            LOG_DEBUG("Play level => {}", GetSelectedLevel());
            // 之後這裡接進 App 的切場景邏輯
        }
    }

    m_WasMousePressed = isMousePressed;
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

void LevelSelectScene::TrySelectCardByMouse() {
    const glm::vec2 mousePos = Util::Input::GetCursorPosition();

    for (int i = 0; i < static_cast<int>(m_LevelCards.size()); ++i) {
        if (m_LevelCards[i]->ContainsPoint(mousePos)) {
            m_SelectedIndex = i;
            m_TargetScrollOffset = -m_SelectedIndex * m_CardSpacing;
            LOG_DEBUG("Mouse select level => {}", m_SelectedIndex + 1);
            return;
        }
    }
}

bool LevelSelectScene::IsPlayButtonClicked(const glm::vec2& mousePos) const {
    const glm::vec2 pos = m_PlayButton->m_Transform.translation;

    const float left = pos.x;
    const float right = pos.x + 220.0f;
    const float top = pos.y;
    const float bottom = pos.y + 90.0f;

    return mousePos.x >= left && mousePos.x <= right &&
           mousePos.y >= top && mousePos.y <= bottom;
}

int LevelSelectScene::GetSelectedLevel() const {
    return m_SelectedIndex + 1;
}