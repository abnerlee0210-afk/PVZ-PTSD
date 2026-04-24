//
// Created by hankl on 2026/3/13.
//
#include "Entity/Sunflower.hpp"
#include "Factory/AnimationFactory.hpp"

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

    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void Sunflower::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    m_GenerateSunTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    UpdateAnimationState();
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

void Sunflower::InitAnimations() {
    auto idle = AnimationFactory::CreateSunflowerIdle();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}