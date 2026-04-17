//
// Created by hankl on 2026/3/13.
//
#include "Entity/Sunflower.hpp"

#include "Util/Time.hpp"

Sunflower::Sunflower(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/Sunflower/Sunflower_0.png",
        row,
        col,
        position,
        100,   // HP
        50     // cost
    ),
      m_GenerateSunTimer(0.0f),
      m_GenerateSunInterval(15.0f) {   // 你可改成 10~15 秒
}

void Sunflower::Update() {
    if (!m_Alive) {
        return;
    }

    m_GenerateSunTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
}

bool Sunflower::CanGenerateSun() const {
    return m_GenerateSunTimer >= m_GenerateSunInterval;
}

glm::vec2 Sunflower::GetSunSpawnPosition() const {
    return m_Transform.translation;
}

void Sunflower::ResetSunTimer() {
    m_GenerateSunTimer = 0.0f;
}