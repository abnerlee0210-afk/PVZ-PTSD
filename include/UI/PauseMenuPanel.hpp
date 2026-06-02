//
// Created by hankl on 2026/6/2.
//

#ifndef PAUSEMENUPANEL_HPP
#define PAUSEMENUPANEL_HPP

#include "pch.hpp"

#include "Screen/BackgroundImage.hpp"
#include "UI/Base/Button.hpp"
#include "Util/Renderer.hpp"

class PauseMenuPanel {
public:
    void Create(Util::Renderer& root);
    void Destroy(Util::Renderer& root);
    void Update();

    bool IsResumeRequested() const { return m_ResumeRequested; }
    bool IsMenuRequested() const { return m_MenuRequested; }

private:
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Button> m_ResumeButton;
    std::shared_ptr<Button> m_MenuButton;

    std::string m_BackgroundPath =
        RESOURCE_DIR "/graphics/Screen/PausePanel.png";

    std::string m_ResumeButtonImage =
        RESOURCE_DIR "/graphics/Screen/resume_button.png";

    std::string m_MenuButtonImage =
        RESOURCE_DIR "/graphics/Screen/menu_button.png";

    bool m_ResumeRequested = false;
    bool m_MenuRequested = false;
    bool m_Created = false;
};

#endif