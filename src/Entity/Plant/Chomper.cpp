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
        5,
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

    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsBiting) {
        m_BiteTimer += dt;

        if (m_BiteTimer >= m_BiteDuration) {
            m_IsBiting = false;
            m_IsDigesting = true;
            m_BiteTimer = 0.0f;
            m_DigestTimer = 0.0f;

            LOG_DEBUG("Chomper started digesting");
        }

        UpdateAnimationState();
        return;
    }

    if (m_IsDigesting) {
        m_DigestTimer += dt;

        if (m_DigestTimer >= m_DigestDuration) {
            m_IsDigesting = false;
            m_DigestTimer = 0.0f;

            LOG_DEBUG("Chomper finished digesting");
        }

        UpdateAnimationState();
        return;
    }

    UpdateAnimationState();
}

bool Chomper::CanBite() const {
    return m_Alive && !m_IsBiting && !m_IsDigesting;
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

    m_IsBiting = true;
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
    if (m_IsBiting) {
        m_AnimController.SetState(PlantAnimState::ATTACK);
    }
    else if (m_IsDigesting) {
        m_AnimController.SetState(PlantAnimState::DIGEST);
    }
    else {
        m_AnimController.SetState(PlantAnimState::IDLE);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}