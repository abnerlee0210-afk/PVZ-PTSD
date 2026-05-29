//
// Created by hankl on 2026/3/10.
//
#include "Entity/Zombie/Zombie.hpp"
#include "Render/RenderLayer.hpp"

#include "Util/Time.hpp"

Zombie::Zombie(const std::string& imagePath,
               int row,
               const glm::vec2& position,
               int hp,
               int ad,
               float speed)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), RenderLayer::ZOMBIE_BASE),
      m_Row(row),
      m_HP(hp),
      m_AD(ad),
      m_Speed(speed),
      m_BaseSpeed(speed),
      m_Alive(true),
      m_AttackTimer(0.0f),
      m_AttackInterval(1.0f),
      m_IsAttacking(false),
      m_IsSlowed(false),
      m_SlowTimer(0.0f),
      m_SlowDuration(5.0f) {
    m_Transform.translation = position;
}

void Zombie::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsSlowed) {
        m_SlowTimer -= deltaTime;

        if (m_SlowTimer <= 0.0f) {
            m_IsSlowed = false;
            m_SlowTimer = 0.0f;
            m_Speed = m_BaseSpeed;
        }
    }

    if (m_IsAttacking) {
        m_AttackTimer += deltaTime;
        UpdateAnimationState();
        return;
    }
    else {
        m_Transform.translation.x -= m_Speed * deltaTime;
    }

    UpdateAnimationState();
}

void Zombie::TakeDamage(int damage) {
    if (!m_Alive) {
        return;
    }

    m_HP -= damage;
    if (m_HP <= 0) {
        m_HP = 0;
        m_Alive = false;
    }
}

bool Zombie::CanAttack() const {
    return m_AttackTimer >= m_AttackInterval;
}

void Zombie::ResetAttackTimer() {
    m_AttackTimer = 0.0f;
}

void Zombie::UpdateAnimationState() {
    if (!m_Alive) {
        m_AnimController.SetState(ZombieAnimState::DIE);
    }
    else if (m_IsAttacking) {
        m_AnimController.SetState(ZombieAnimState::ATTACK);
    }
    else {
        m_AnimController.SetState(ZombieAnimState::WALK);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}

void Zombie::ApplySlow() {
    m_IsSlowed = true;
    m_SlowTimer = m_SlowDuration;
    m_Speed = m_BaseSpeed * 0.5f;

}