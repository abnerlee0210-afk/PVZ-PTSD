//
// Created by LAB1223 on 2026/5/29.
//
#include "Entity/Plant/SnowPeashooter.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Time.hpp"

SnowPeashooter::SnowPeashooter(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/SnowPea/SnowPea_0.png",
        row,
        col,
        position,
        100,
        175
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void SnowPeashooter::Update() {
    if (!m_Alive) {
        return;
    }

    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;

    UpdateAnimationState();
}

bool SnowPeashooter::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

glm::vec2 SnowPeashooter::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 35.0f;
    pos.y += 5.0f;
    return pos;
}

void SnowPeashooter::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}

ProjectileType SnowPeashooter::GetProjectileType() const {
    return ProjectileType::SNOW_PEA;
}

void SnowPeashooter::InitAnimations() {
    auto idle = AnimationFactory::CreateSnowPeashooterIdle();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}

void SnowPeashooter::UpdateAnimationState() {
    if (!m_Alive) {
        m_AnimController.SetState(PlantAnimState::DIE);
    }
    else {
        m_AnimController.SetState(PlantAnimState::IDLE);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}