//
// Created by hankl on 2026/3/13.
//
#include "Entity/Sun.hpp"

#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"


// 固定位置生成
Sun::Sun(const glm::vec2& position, int value, float lifetime)
    : Util::GameObject(std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Plants/Sun/Sun_0.png"), 12.0f),
      m_Value(value),
      m_Alive(true),
      m_HalfWidth(40.0f),
      m_HalfHeight(40.0f),
      m_IsFalling(false),
      m_TargetPosition(position),
      m_FallSpeed(120.0f),
      m_LifeTimer(0.0f),
      m_LifeTime(lifetime) {
    m_Transform.translation = position;
    InitAnimations();
    m_AnimController.SetState(SunAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

// 掉落式生成
Sun::Sun(const glm::vec2& startPosition, const glm::vec2& targetPosition, int value, float lifetime)
    : Util::GameObject(std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Plants/Sun/Sun_0.png"), 12.0f),
      m_Value(value),
      m_Alive(true),
      m_HalfWidth(40.0f),
      m_HalfHeight(40.0f),
      m_IsFalling(true),
      m_TargetPosition(targetPosition),
      m_FallSpeed(100.0f),
      m_LifeTimer(0.0f),
      m_LifeTime(lifetime) {
    m_Transform.translation = startPosition;
    InitAnimations();
    m_AnimController.SetState(SunAnimState::IDLE);
    m_State = SunState::FALLING;
    SetDrawable(m_AnimController.GetCurrentAnimation());
}



// void Sun::Update() {
//     if (!m_Alive) {
//         return;
//     }
//     UpdateAnimationState();
//     const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;
//     // 往下掉，所以 Y 要減掉速度
//     if (m_IsFalling) {
//         m_Transform.translation.y -= m_FallSpeed * deltaTime;
//     }
//
//     // 當目前的 Y 比目標還要「低」時，停止掉落
//     // 在中心 (0,0) 的坐標系，越下面數字越小 (例如 -100 比 200 小)
//     if (m_Transform.translation.y <= m_TargetPosition.y) {
//         m_Transform.translation.y = m_TargetPosition.y;
//         m_IsFalling = false;
//     }
//
//     m_LifeTimer += deltaTime;
//     if (m_LifeTimer >= m_LifeTime) {
//         m_Alive = false;
//     }
// }

void Sun::Update() {
    if (!m_Alive) return;

    UpdateAnimationState();
    const float deltaTime = static_cast<float>(Util::Time::GetDeltaTimeMs()) / 1000.0f;

    switch (m_State) {
        case SunState::FALLING:
            m_Transform.translation.y -= m_FallSpeed * deltaTime;
            if (m_Transform.translation.y <= m_TargetPosition.y) {
                m_Transform.translation.y = m_TargetPosition.y;
                m_State = SunState::IDLE;
            }
            break;

        case SunState::IDLE:
            m_LifeTimer += deltaTime;
            if (m_LifeTimer >= m_LifeTime) {
                m_Alive = false; // 時間到消失
            }
            break;

        case SunState::FLYING:
            // 飛向左上角 UI 點
            // 這裡使用 Lerp，速度係數可以調高一點（例如 8.0f）讓它有吸過去的感覺
            m_Transform.translation = glm::mix(m_Transform.translation, m_UIPosition, 8.0f * deltaTime);

            // 同時縮小陽光，模擬縮進計分板的效果
            m_Transform.scale = glm::mix(m_Transform.scale, glm::vec2(0.3f, 0.3f), 5.0f * deltaTime);

            // 判斷是否夠靠近目標點了
            if (glm::distance(m_Transform.translation, m_UIPosition) < 10.0f) {
                m_Alive = false;
                // 這裡應該觸發 UI 數值增加，見下方的 Collect 說明
            }
            break;
    }
}

void Sun::Collect() {
    m_State = SunState::FLYING;
}

bool Sun::ContainsPoint(const glm::vec2& point) const {
    const float left = m_Transform.translation.x - m_HalfWidth;
    const float right = m_Transform.translation.x + m_HalfWidth;
    const float top = m_Transform.translation.y - m_HalfHeight;
    const float bottom = m_Transform.translation.y + m_HalfHeight;

    return point.x >= left && point.x <= right &&
           point.y >= top && point.y <= bottom;
}

void Sun::InitAnimations() {
    auto idle = AnimationFactory::CreateSunIdle();

    m_AnimController.AddAnimation(SunAnimState::IDLE, idle);
}

void Sun::UpdateAnimationState() {
    if (!m_Alive) {
        return;
    }
    else {
        m_AnimController.SetState(SunAnimState::IDLE);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}