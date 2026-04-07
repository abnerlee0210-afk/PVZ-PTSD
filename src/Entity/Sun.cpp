//
// Created by hankl on 2026/3/13.
//
#include "Entity/Sun.hpp"

#include "Util/Time.hpp"

// 固定位置生成
Sun::Sun(const glm::vec2& position, int value)
    : Util::GameObject(std::make_shared<Util::Image>(RESOURCE_DIR "/sun.png"), 12.0f),
      m_Value(value),
      m_Alive(true),
      m_HalfWidth(40.0f),
      m_HalfHeight(40.0f),
      m_IsFalling(false),
      m_TargetPosition(position),
      m_FallSpeed(120.0f) {
    m_Transform.translation = position;
}

// 掉落式生成
Sun::Sun(const glm::vec2& startPosition, const glm::vec2& targetPosition, int value)
    : Util::GameObject(std::make_shared<Util::Image>(RESOURCE_DIR "/sun.png"), 12.0f),
      m_Value(value),
      m_Alive(true),
      m_HalfWidth(40.0f),
      m_HalfHeight(40.0f),
      m_IsFalling(true),
      m_TargetPosition(targetPosition),
      m_FallSpeed(120.0f) {
    m_Transform.translation = startPosition;
}



void Sun::Update() {
    if (!m_Alive || !m_IsFalling) {
        return;
    }
    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;
    // 往下掉，所以 Y 要減掉速度
    m_Transform.translation.y -= m_FallSpeed * deltaTime;

    // 當目前的 Y 比目標還要「低」時，停止掉落
    // 在中心 (0,0) 的坐標系，越下面數字越小 (例如 -100 比 200 小)
    if (m_Transform.translation.y <= m_TargetPosition.y) {
        m_Transform.translation.y = m_TargetPosition.y;
        m_IsFalling = false;
    }
}

void Sun::Collect() {
    m_Alive = false;
}

bool Sun::ContainsPoint(const glm::vec2& point) const {
    const float left = m_Transform.translation.x - m_HalfWidth;
    const float right = m_Transform.translation.x + m_HalfWidth;
    const float top = m_Transform.translation.y - m_HalfHeight;
    const float bottom = m_Transform.translation.y + m_HalfHeight;

    return point.x >= left && point.x <= right &&
           point.y >= top && point.y <= bottom;
}