//
// Created by 李政翰 on 2026/4/1.
//

#ifndef LEVELSELECTSCENE_HPP
#define LEVELSELECTSCENE_HPP

#include "pch.hpp"

#include "UI/LevelCard.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Renderer.hpp"

class LevelSelectScene {
public:
    LevelSelectScene();

    void Update();

    int GetSelectedLevel() const;

private:
    void HandleInput();
    void UpdateCardPositions();
    void UpdateSelectionVisual();
    void TrySelectCardByMouse();
    bool IsPlayButtonClicked(const glm::vec2& mousePos) const;

private:
    Util::Renderer m_Renderer;

    std::shared_ptr<Util::GameObject> m_Background;
    std::shared_ptr<Util::GameObject> m_PlayButton;

    std::vector<std::shared_ptr<LevelCard>> m_LevelCards;

    int m_SelectedIndex = 0;
    bool m_WasMousePressed = false;

    float m_CurrentScrollOffset = 0.0f;
    float m_TargetScrollOffset = 0.0f;

    float m_CardSpacing = 220.0f;
    float m_CenterX = 760.0f;
    float m_CardY = 0.0f;
};

#endif //LEVELSELECTSCENE_HPP
