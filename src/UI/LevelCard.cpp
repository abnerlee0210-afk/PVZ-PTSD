//
// Created by 李政翰 on 2026/3/31.
//
#include "UI/LevelCard.hpp"

LevelCard::LevelCard(int levelId,
                     const std::string &imagePath,
                     const glm::vec2 &position,
                     bool unlocked)
    : m_LevelId(levelId),
      m_Unlocked(unlocked),
      m_Selected(false),
      m_Position(position),
      m_Width(180.0f),
      m_Height(260.0f) {
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

glm::vec2 LevelCard::GetSize() const {
    auto img = std::dynamic_pointer_cast<Util::Image>(m_ImageObject);
    return img ? glm::vec2(img->GetSize().x, img->GetSize().y) : glm::vec2(0.0);
}

bool LevelCard::IsMouseHovering() const {
    glm::vec2 mousePos = Util::Input::GetCursorPosition(); // 滑鼠位置
    glm::vec2 pos = m_Transform.translation; // 圖片中心位置
    glm::vec2 size = GetSize(); // 圖片長寬

    return (mousePos.x >= pos.x - size.x / 2 &&
            mousePos.x <= pos.x + size.x / 2 &&
            mousePos.y >= pos.y - size.y / 2 &&
            mousePos.y <= pos.y + size.y / 2);
}





bool LevelCard::ContainsPoint(const glm::vec2& point) const {
    const float left = m_Position.x;
    const float right = m_Position.x + m_Width;
    const float top = m_Position.y;
    const float bottom = m_Position.y + m_Height;

    return point.x >= left && point.x <= right &&
           point.y >= top && point.y <= bottom;
}