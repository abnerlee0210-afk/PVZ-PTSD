//
// Created by hankl on 2026/6/2.
//
#include "UI/PauseMenuPanel.hpp"
#include "Render/RenderLayer.hpp"

#include "Util/Logger.hpp"

void PauseMenuPanel::Create(Util::Renderer& root) {
    if (m_Created) {
        return;
    }

    m_ResumeRequested = false;
    m_MenuRequested = false;

    m_Background = std::make_shared<BackgroundImage>(
        m_BackgroundPath
    );
    m_Background->SetZIndex(RenderLayer::PAUSE_SCREEN);
    m_Background->m_Transform.translation = {0.0f, 0.0f};
    root.AddChild(m_Background);

    m_ResumeButton = std::make_shared<Button>(
        RESOURCE_DIR "/graphics/Screen/resume_button.png",
        glm::vec2(-150.0f, -150.0f)
    );
    m_ResumeButton->SetZIndex(RenderLayer::PAUSE_SCREEN_BUTTON);

    m_MenuButton = std::make_shared<Button>(
        RESOURCE_DIR "/graphics/Screen/menu_button.png",
        glm::vec2(150.0f, -150.0f)
    );
    m_MenuButton->SetZIndex(RenderLayer::PAUSE_SCREEN_BUTTON);

    m_ResumeButton->SetCallback([this]() {
        m_ResumeRequested = true;
        LOG_DEBUG("Resume requested");
    });

    m_MenuButton->SetCallback([this]() {
        m_MenuRequested = true;
        LOG_DEBUG("Return menu requested");
    });

    root.AddChild(m_ResumeButton);
    root.AddChild(m_MenuButton);

    m_Created = true;
}

void PauseMenuPanel::Destroy(Util::Renderer& root) {
    if (m_Background) {
        root.RemoveChild(m_Background);
        m_Background = nullptr;
    }

    if (m_ResumeButton) {
        root.RemoveChild(m_ResumeButton);
        m_ResumeButton = nullptr;
    }

    if (m_MenuButton) {
        root.RemoveChild(m_MenuButton);
        m_MenuButton = nullptr;
    }

    m_ResumeRequested = false;
    m_MenuRequested = false;
    m_Created = false;
}

void PauseMenuPanel::Update() {
    if (m_ResumeButton) {
        m_ResumeButton->Update();

        if (m_ResumeButton->IsMouseHovering()) {
            m_ResumeButton->SetVisualScaleFactor(1.08f);
        } else {
            m_ResumeButton->SetVisualScaleFactor(1.0f);
        }
    }

    if (m_MenuButton) {
        m_MenuButton->Update();

        if (m_MenuButton->IsMouseHovering()) {
            m_MenuButton->SetVisualScaleFactor(1.08f);
        } else {
            m_MenuButton->SetVisualScaleFactor(1.0f);
        }
    }
}