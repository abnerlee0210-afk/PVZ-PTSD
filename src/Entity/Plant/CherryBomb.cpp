//
// Created by hankl on 2026/5/12.
//
#include "Entity/Plant/CherryBomb.hpp"

#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"

CherryBomb::CherryBomb(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/CherryBomb/CherryBomb_0.png",
        row,
        col,
        position,
        9999,
        150
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::ATTACK);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void CherryBomb::Update() {
    if (!m_Alive || m_HasExploded) {
        return;
    }

    m_ExplodeTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    UpdateAnimationState();
}

bool CherryBomb::CanExplode() const {
    return !m_HasExploded && m_ExplodeTimer >= m_ExplodeDelay;
}

glm::vec2 CherryBomb::GetExplosionCenter() const {
    return m_Transform.translation;
}

float CherryBomb::GetExplosionRadius() const {
    return 150.0f;
}

int CherryBomb::GetExplosionDamage() const {
    return 99999;
}

void CherryBomb::MarkExploded() {
    m_HasExploded = true;
    m_Alive = false;
}

void CherryBomb::InitAnimations() {
    auto explode = AnimationFactory::CreateCherryBombexplode();

    m_AnimController.AddAnimation(PlantAnimState::ATTACK, explode);
}

void CherryBomb::UpdateAnimationState() {
    m_AnimController.SetState(PlantAnimState::ATTACK);

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}