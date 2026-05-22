#include "Entity/Chomper.hpp"

#include <limits>

#include "Factory/AnimationFactory.hpp"
#include "Util/Time.hpp"

Chomper::Chomper(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/Chomper/Chomper/Chomper_0.png",
        row,
        col,
        position,
        150,
        150) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void Chomper::Update() {
    const std::vector<std::shared_ptr<Zombie>> zombies;
    UpdateWithZombies(zombies);
}

void Chomper::UpdateWithZombies(const std::vector<std::shared_ptr<Zombie>>& zombies) {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    switch (m_State) {
        case ChomperState::IDLE: {
            auto target = FindTarget(zombies);
            if (target) {
                EnterAttacking(target);
            }
            break;
        }
        case ChomperState::ATTACKING:
            m_AttackTimer += deltaTime;
            if (m_AttackTimer >= m_AttackDuration) {
                EnterChewing();
            }
            break;
        case ChomperState::CHEWING:
            m_ChewTimer += deltaTime;
            if (m_ChewTimer >= m_ChewDuration) {
                EnterIdle();
            }
            break;
    }

    UpdateAnimationForState();
}

std::shared_ptr<Zombie> Chomper::FindTarget(
    const std::vector<std::shared_ptr<Zombie>>& zombies
) const {
    std::shared_ptr<Zombie> nearestTarget = nullptr;
    float nearestDistance = std::numeric_limits<float>::max();
    const float chomperX = m_Transform.translation.x;

    for (const auto& zombie : zombies) {
        if (!zombie || !zombie->IsAlive()) {
            continue;
        }

        if (zombie->GetRow() != m_Row) {
            continue;
        }

        const float dx = zombie->GetTransform().translation.x - chomperX;
        if (dx < 0.0f || dx > m_DetectRange) {
            continue;
        }

        if (dx < nearestDistance) {
            nearestDistance = dx;
            nearestTarget = zombie;
        }
    }

    return nearestTarget;
}

void Chomper::EnterIdle() {
    m_State = ChomperState::IDLE;
    m_AttackTimer = 0.0f;
    m_ChewTimer = 0.0f;
}

void Chomper::EnterAttacking(const std::shared_ptr<Zombie>& target) {
    if (!target || !target->IsAlive()) {
        return;
    }

    m_State = ChomperState::ATTACKING;
    m_AttackTimer = 0.0f;
    target->TakeDamage(99999);
}

void Chomper::EnterChewing() {
    m_State = ChomperState::CHEWING;
    m_AttackTimer = 0.0f;
    m_ChewTimer = 0.0f;
}

void Chomper::UpdateAnimationForState() {
    if (!m_Alive) {
        m_AnimController.SetState(PlantAnimState::DIE);
    } else if (m_State == ChomperState::ATTACKING) {
        m_AnimController.SetState(PlantAnimState::ATTACK);
    } else if (m_State == ChomperState::CHEWING) {
        m_AnimController.SetState(PlantAnimState::CHEWING);
    } else {
        m_AnimController.SetState(PlantAnimState::IDLE);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}

void Chomper::InitAnimations() {
    auto idle = AnimationFactory::CreateChomperIdle();
    auto attack = AnimationFactory::CreateChomperAttack();
    auto digest = AnimationFactory::CreateChomperDigest();

    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(PlantAnimState::CHEWING, digest);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}
