//
// Created by hankl on 2026/3/10.
//
#include "Entity/Zombie/Zombie.hpp"
#include "Render/RenderLayer.hpp"

#include "Util/Time.hpp"
#include "Render/RenderLayer.hpp"

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
    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsDying) {
        m_DieTimer += deltaTime;

        UpdateAnimationState();
        UpdateZIndexByY();

        if (m_DieTimer >= m_DieDuration) {
            m_ShouldRemove = true;
        }

        return;
    }

    if (!m_Alive) {
        return;
    }

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
    UpdateZIndexByY();
}

void Zombie::TakeDamage(int damage) {
    if (!m_Alive || m_IsDying) {
        return;
    }

    m_HP -= damage;

    if (m_HP <= 0) {
        m_HP = 0;
        StartDying(ZombieDeathType::NORMAL);
    }
}

bool Zombie::CanAttack() const {
    return m_AttackTimer >= m_AttackInterval;
}

void Zombie::ResetAttackTimer() {
    m_AttackTimer = 0.0f;
}

void Zombie::UpdateAnimationState() {
    if (m_IsDying) {
        if (m_DeathType == ZombieDeathType::BOOM) {
            m_AnimController.SetState(ZombieAnimState::BOOM_DIE);
        } else {
            m_AnimController.SetState(ZombieAnimState::DIE);
        }
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


void Zombie::UpdateZIndexByY() {
    SetZIndex(RenderLayer::WorldYSort(RenderLayer::ZOMBIE_BASE, m_Transform.translation.y));
}

void Zombie::TakeDamageByExplosion(int damage) {
    if (!m_Alive || m_IsDying) {
        return;
    }

    m_HP -= damage;

    if (m_HP <= 0) {
        m_HP = 0;
        StartDying(ZombieDeathType::BOOM);
    }
}

void Zombie::BeEaten() {
    if (m_ShouldRemove) {
        return;
    }

    m_HP = 0;
    m_Alive = false;
    m_IsDying = false;
    m_ShouldRemove = true;
    m_IsAttacking = false;
    m_DeathType = ZombieDeathType::EATEN;
}

void Zombie::StartDying(ZombieDeathType deathType) {
    m_Alive = false;
    m_IsDying = true;
    m_ShouldRemove = false;
    m_DieTimer = 0.0f;
    m_IsAttacking = false;
    m_DeathType = deathType;

    if (deathType == ZombieDeathType::BOOM) {
        m_DieDuration = 0.6f;
    } else {
        m_DieDuration = 0.8f;
    }

    UpdateAnimationState();
}