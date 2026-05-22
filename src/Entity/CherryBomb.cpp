#include "Entity/CherryBomb.hpp"

#include "Factory/AnimationFactory.hpp"
#include "Util/Time.hpp"

CherryBomb::CherryBomb(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/CherryBomb/CherryBomb_0.png",
        row,
        col,
        position,
        150,
        150),
      m_ExplodeTimer(0.0f),
      m_ExplodeDelay(1.2f),
      m_Exploded(false) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void CherryBomb::Update() {
    if (!m_Alive || m_Exploded) {
        UpdateAnimationState();
        return;
    }

    m_ExplodeTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    if (m_ExplodeTimer >= m_ExplodeDelay) {
        m_Exploded = true;
    }

    UpdateAnimationState();
}

void CherryBomb::InitAnimations() {
    auto explodeAnim = AnimationFactory::CreateCherryBombExplode();
    m_AnimController.AddAnimation(PlantAnimState::IDLE, explodeAnim);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, explodeAnim);
    m_AnimController.AddAnimation(PlantAnimState::DIE, explodeAnim);
}
