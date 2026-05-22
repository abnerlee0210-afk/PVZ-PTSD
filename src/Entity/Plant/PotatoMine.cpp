#include "Entity/Plant/PotatoMine.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Time.hpp"
#include "Util/Logger.hpp"

PotatoMine::PotatoMine(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/PotatoMine/PotatoMineInit/PotatoMineInit_0.png",
        row,
        col,
        position,
        100,
        25
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::INIT);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void PotatoMine::Update() {
    if (!m_Alive) {
        return;
    }

    const float dt = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsExploding) {
        m_ExplodeTimer += dt;

        if (m_ExplodeTimer >= m_ExplodeDuration) {
            m_HasExploded = true;
            m_Alive = false;
        }

        UpdateAnimationState();
        return;
    }

    if (!m_IsArmed) {
        m_ArmTimer += dt;

        if (m_ArmTimer >= m_ArmDelay) {
            m_IsArmed = true;
            m_ArmedGraceTimer = 0.0f;
            LOG_DEBUG("PotatoMine armed at row={}, col={}", m_Row, m_Col);
        }
    }
    else {
        m_ArmedGraceTimer += dt;
    }

    UpdateAnimationState();
}

bool PotatoMine::CanExplodeOnContact() const {
    return m_Alive &&
           m_IsArmed &&
           !m_IsExploding &&
           !m_HasExploded &&
           m_ArmedGraceTimer >= m_ArmedGraceDuration;
}

int PotatoMine::GetContactExplosionDamage() const {
    return 99999;
}

void PotatoMine::TriggerContactExplosion() {
    if (!CanExplodeOnContact()) {
        return;
    }

    m_IsExploding = true;
    m_ExplodeTimer = 0.0f;

    LOG_DEBUG("PotatoMine explosion animation started at row={}, col={}", m_Row, m_Col);

    UpdateAnimationState();
}

void PotatoMine::InitAnimations() {
    auto init = AnimationFactory::CreatePotatoMineInit();
    auto armed = AnimationFactory::CreatePotatoMineArmed();
    auto explode = AnimationFactory::CreatePotatoMineExplode();

    m_AnimController.AddAnimation(PlantAnimState::INIT, init);
    m_AnimController.AddAnimation(PlantAnimState::ARMED, armed);
    m_AnimController.AddAnimation(PlantAnimState::EXPLODE, explode);
}

void PotatoMine::UpdateAnimationState() {
    if (m_IsExploding) {
        m_AnimController.SetState(PlantAnimState::EXPLODE);
    }
    else if (m_IsArmed) {
        m_AnimController.SetState(PlantAnimState::ARMED);
    }
    else {
        m_AnimController.SetState(PlantAnimState::INIT);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}