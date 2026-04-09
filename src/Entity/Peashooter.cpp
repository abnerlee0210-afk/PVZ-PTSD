//
// Created by hankl on 2026/3/10.
//
#include "Entity/Peashooter.hpp"

#include "Util/Time.hpp"

Peashooter::Peashooter(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/Peashooter/Peashooter_0.png",
        row,
        col,
        position,
        100,
        100
    ),
      m_ShootTimer(0.0f),
      m_ShootInterval(1.5f) {
}

void Peashooter::Update() {
    if (!m_Alive) {
        return;
    }

    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
}

bool Peashooter::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

glm::vec2 Peashooter::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 35.0f;
    return pos;
}

void Peashooter::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}