//
// Created by 李政翰 on 2026/4/1.
//
#ifndef LEVELSELECTSCENE_HPP
#define LEVELSELECTSCENE_HPP

#include "pch.hpp"
#include <memory>

#include "Scene.hpp"
#include "Screen/BackgroundImage.hpp"
#include "UI/Button.hpp"
#include "UI/LevelCard.hpp"

#include "Util/Renderer.hpp"
#include "Util/Logger.hpp"
#include "Util/Input.hpp"
#include "functional"
#include <iostream>

class LevelSelectScene : public Scene
{
public:
    LevelSelectScene();
    ~LevelSelectScene();

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

    int GetSelectedLevel() const;
private:
    void HandleInput();
    void UpdateCardPositions();
    void UpdateSelectionVisual();

private:
    // LevelSelectScene 物件
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Button> m_BackButton;
    std::shared_ptr<Button> m_PlayButton;
    std::vector<std::shared_ptr<LevelCard>> m_LevelCards;

    // 圖片資源Path
    std::string BackgroundImagePath = RESOURCE_DIR "/graphics/Screen/select_bg.png";
    std::string BackButtonImage = RESOURCE_DIR "/graphics/Screen/back_button.png";
    std::string BackButtonFeedback = RESOURCE_DIR "/graphics/Screen/back_button_2.png";
    std::string PlayButtonImage = RESOURCE_DIR "/graphics/Screen/play_button.png";
    std::string PlayButtonFeedback = RESOURCE_DIR "/graphics/Screen/play_button_2.png";
    std::string LevelCardImage = RESOURCE_DIR "/graphics/Screen/LevelCard/level_";

    // 屬性
    int m_SelectedIndex = 0;
    // bool m_WasMousePressed = false;

    float m_CurrentScrollOffset = 0.0f;
    float m_TargetScrollOffset = 0.0f;

    float m_CardSpacing = 180.0f;
    float m_CenterX = 0.0f;  // 所選關卡的圖片X
    float m_CardY = 110.0f;
};

#endif //LEVELSELECTSCENE_HPP