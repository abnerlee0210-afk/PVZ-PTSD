//
// Created by hankl on 2026/5/31.
//
#include "Entity/Plant/Chomper.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Time.hpp"
#include "Util/Logger.hpp"

Chomper::Chomper(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/Chomper/Chomper/Chomper_0.png",
        row,
        col,
        position,
        100,
        150
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
    m_Transform.translation.x += 20;
    m_Transform.translation.y += 20;
}

void Chomper::Update() {
    if (!m_Alive) {
        return;
    }

    if (m_IsDigesting) {
        m_AnimController.SetState(PlantAnimState::DIGEST);
        m_DigestTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;

        if (m_DigestTimer >= m_DigestDuration) {
            m_IsDigesting = false;
            m_DigestTimer = 0.0f;

            LOG_DEBUG("Chomper finished digesting");
        }
    }
    UpdateAnimationState();
}

bool Chomper::CanBite() const {
    return m_Alive && !m_IsDigesting;
}

bool Chomper::IsDigesting() const {
    return m_IsDigesting;
}

float Chomper::GetBiteRange() const {
    return m_BiteRange;
}

void Chomper::BiteZombie() {
    if (!CanBite()) {
        return;
    }
    m_AnimController.SetState(PlantAnimState::ATTACK);

    m_IsDigesting = true;
    m_DigestTimer = 0.0f;

    LOG_DEBUG("Chomper bit zombie");
}

void Chomper::InitAnimations() {
    auto idle = AnimationFactory::CreateChomperIdle();
    auto attack = AnimationFactory::CreateChomperAttack();
    auto digest = AnimationFactory::CreateChomperDigest();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(PlantAnimState::DIGEST, digest);
}

void Chomper::UpdateAnimationState() {
    if ((! m_IsDigesting) && (m_AnimController.GetState() != PlantAnimState::ATTACK)) {
        m_AnimController.SetState(PlantAnimState::IDLE);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}