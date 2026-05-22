//
// Created by hankl on 2026/3/13.
//

#ifndef SUN_HPP
#define SUN_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Animation/AnimationStateController.hpp"

enum class SunState {
    FALLING,   // 掉落中
    IDLE,      // 停在地上等待收集
    FLYING     // 被點擊後飛向 UI
};

enum class SunAnimState {
    IDLE,
};

class Sun : public Util::GameObject {
public:
    Sun(const glm::vec2& position, int value = 25, float lifetime = 8.0f);
    Sun(const glm::vec2& startPosition, const glm::vec2& targetPosition,
        int value = 25, float lifetime = 8.0f);


    int GetValue() const { return m_Value; }
    bool IsAlive() const { return m_Alive; }

    void Update();
    void Collect();
    bool ContainsPoint(const glm::vec2& point) const;

    void InitAnimations();
    void UpdateAnimationState();

private:
    int m_Value;
    bool m_Alive;
    float m_HalfWidth;
    float m_HalfHeight;

    bool m_IsFalling;
    glm::vec2 m_TargetPosition;
    float m_FallSpeed;

    float m_LifeTimer;
    float m_LifeTime;

    SunState m_State;
    glm::vec2 m_UIPosition = glm::vec2(-385.0f, 230.0f);

    AnimationStateController<SunAnimState> m_AnimController;
};

#endif //SUN_HPP