#include "UI/ShovelButton.hpp"

ShovelButton::ShovelButton(const std::string& imagePath, const glm::vec2& position)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), 35.0f),
      m_Selected(false),
      m_Width(90.0f),
      m_Height(90.0f) {
    m_Transform.translation = position;
}

bool ShovelButton::ContainsPoint(const glm::vec2& point) const {
    const float left = m_Transform.translation.x - m_Width/2;
    const float right = m_Transform.translation.x + m_Width/2;
    const float top = m_Transform.translation.y + m_Height/2;
    const float bottom = m_Transform.translation.y - m_Height/2;

    return point.x >= left && point.x <= right &&
           point.y <= top && point.y >= bottom;
}

void ShovelButton::SetSelected(bool selected) {
    m_Selected = selected;

    if (m_Selected) {
        m_Transform.scale = {1.1f, 1.1f};
    } else {
        m_Transform.scale = {1.0f, 1.0f};
    }
}