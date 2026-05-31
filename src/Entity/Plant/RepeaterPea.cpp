//
// Created by hankl on 2026/5/31.
//
#include "Entity/Plant/RepeaterPea.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Time.hpp"

RepeaterPea::RepeaterPea(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/RepeaterPea/RepeaterPea_0.png",
        row,
        col,
        position,
        100,
        200
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void RepeaterPea::Update() {
    if (!m_Alive) {
        return;
    }

    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;

    UpdateAnimationState();

}

bool RepeaterPea::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

glm::vec2 RepeaterPea::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 10.0f;
    return pos;
}

void RepeaterPea::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}

ProjectileType RepeaterPea::GetProjectileType() const {
    return ProjectileType::PEA;
}

std::vector<float> RepeaterPea::GetProjectileFireDelays() const {
    return {
        0.0f,
        0.25f
    };
}

void RepeaterPea::InitAnimations() {
    auto idle = AnimationFactory::CreateRepeaterPeaIdle();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}

void RepeaterPea::UpdateAnimationState() {
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