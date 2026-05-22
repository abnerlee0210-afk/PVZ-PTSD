#include "Entity/RepeaterPea.hpp"

#include "Factory/AnimationFactory.hpp"
#include "Util/Time.hpp"

RepeaterPea::RepeaterPea(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/RepeaterPea/RepeaterPea_0.png",
        row,
        col,
        position,
        100,
        200),
      m_ShootInterval(1.5f),
      m_ShootTimer(0.0f) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void RepeaterPea::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    UpdateAnimationState();
}

bool RepeaterPea::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

ProjectileType RepeaterPea::GetProjectileType() const {
    return ProjectileType::PEA;
}

glm::vec2 RepeaterPea::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 30.0f;
    return pos;
}

int RepeaterPea::GetProjectileCountPerShot() const {
    return 2;
}

glm::vec2 RepeaterPea::GetProjectileSpawnPositionByIndex(int projectileIndex) const {
    glm::vec2 pos = GetProjectileSpawnPosition();
    pos.x += static_cast<float>(projectileIndex) * 18.0f;
    return pos;
}

void RepeaterPea::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}

void RepeaterPea::InitAnimations() {
    auto idle = AnimationFactory::CreateRepeaterPeaIdle();
    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}
