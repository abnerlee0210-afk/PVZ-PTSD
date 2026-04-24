//
// Created by hankl on 2026/3/10.
//
#include "Entity/Peashooter.hpp"

#include "Level/LevelTypes.hpp"
#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"

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
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void Peashooter::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    UpdateAnimationState();
}

bool Peashooter::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

ProjectileType Peashooter::GetProjectileType() const {
    return ProjectileType::PEA;
}

glm::vec2 Peashooter::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 10.0f;
    return pos;
}

void Peashooter::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}

void Peashooter::InitAnimations() {
    auto idle = AnimationFactory::CreatePeashooterIdle();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}