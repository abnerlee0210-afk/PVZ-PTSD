//
// Created by 李政翰 on 2026/3/31.
//
#include "UI/LevelCard.hpp"

LevelCard::LevelCard(int levelId,
                     const std::string &imagePath,
                     const glm::vec2 &position
                     )
    : m_LevelId(levelId),
      m_Selected(false),
      m_Position(position) {
    auto image = std::make_shared<Util::Image>(imagePath);
    m_ImageObject = std::make_shared<Util::GameObject>(image, 20.0f);
    m_ImageObject->m_Transform.translation = position;
    m_ImageObject->m_Transform.scale = {1.0f, 1.0f};
}

void LevelCard::SetPosition(const glm::vec2& position) {
    m_Position = position;
    m_ImageObject->m_Transform.translation = position;
    // m_TextObject->m_Transform.translation = {position.x + 15.0f , position.y + 130.0f};
}

void LevelCard::SetSelected(bool selected) {
    m_Selected = selected;

    if (m_Selected) {
        m_ImageObject->m_Transform.scale = {1.2f, 1.2f};
    } else {
        m_ImageObject->m_Transform.scale = {0.8f, 0.8f};
    }
}




