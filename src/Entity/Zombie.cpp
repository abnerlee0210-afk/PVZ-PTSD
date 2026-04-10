//
// Created by hankl on 2026/3/10.
//
#include "Entity/Zombie.hpp"

#include "Util/Time.hpp"

Zombie::Zombie(const std::string& imagePath,
               int row,
               const glm::vec2& position,
               int hp,
               float speed)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), 10.0f),
      m_Row(row),
      m_HP(hp),
      m_Speed(speed),
      m_Alive(true),
      m_AttackTimer(0.0f),
      m_AttackInterval(1.0f),
      m_IsAttacking(false) {
    m_Transform.translation = position;
}

void Zombie::Update() {
    if (!m_Alive) {
        return;
    }

    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsAttacking) {
        m_AttackTimer += deltaTime;
        return;
    }

    m_Transform.translation.x -= m_Speed * deltaTime;

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

