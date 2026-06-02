//
// Created by 李政翰 on 2026/5/13.
//
#include "Entity/Zombie/PoleVaultingZombie.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Time.hpp"

PoleVaultingZombie::PoleVaultingZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/PoleVaultingZombie/PoleVaultingZombie_run/1.png",
        row,
        position,
        30,
        30,
        30.0f
    ) {
    m_Speed = m_PoleSpeed;
    InitAnimations();
    m_AnimController.SetState(ZombieAnimState::RUN);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void PoleVaultingZombie::Update() {
    if (m_IsDying || !m_Alive) {
        Zombie::Update();
        return;
    }

    float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_IsJumping) {
        m_JumpTimer += deltaTime;

        float t = m_JumpTimer / m_JumpDuration;
        if (t > 1.0f) {
            t = 1.0f;
        }

        m_Transform.translation.x =
            m_JumpStartPos.x + (m_JumpTargetPos.x - m_JumpStartPos.x) * t;

        float jumpHeight = 45.0f;
        float arc = 4.0f * t * (1.0f - t);

        m_Transform.translation.y =
            m_JumpStartPos.y +
            (m_JumpTargetPos.y - m_JumpStartPos.y) * t +
            jumpHeight * arc;

        UpdateAnimationState();
        UpdateZIndexByY();

        if (m_JumpTimer >= m_JumpDuration) {
            m_IsJumping = false;
            m_HasPole = false;
            m_Speed = m_NormalSpeed;
            m_Transform.translation = m_JumpTargetPos;
        }

        return;
    }

    Zombie::Update();
}

bool PoleVaultingZombie::CanJumpOverPlant() const {
    return m_Alive && m_HasPole && !m_IsJumping;
}

void PoleVaultingZombie::StartJumpOverPlant(const glm::vec2& plantPos) {
    if (!CanJumpOverPlant()) {
        return;
    }

    m_IsJumping = true;
    m_JumpTimer = 0.0f;

    m_JumpStartPos = m_Transform.translation;

    // 殭屍往左走，所以跳到植物左邊一點
    m_JumpTargetPos = plantPos;
    m_JumpTargetPos.x -= 50.0f;
}

void PoleVaultingZombie::InitAnimations() {
    auto run = AnimationFactory::CreatePoleVaultingZombieRun();
    auto jump = AnimationFactory::CreatePoleVaultingZombieJump();
    auto walk = AnimationFactory::CreatePoleVaultingZombieWalk();
    auto attack = AnimationFactory::CreatePoleVaultingZombieAttack();
    auto die = AnimationFactory::CreateZombieDie();

    m_AnimController.AddAnimation(ZombieAnimState::RUN, run);
    m_AnimController.AddAnimation(ZombieAnimState::JUMP, jump);
    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, die);
}

void PoleVaultingZombie::UpdateAnimationState() {
    if (m_IsDying) {
        m_AnimController.SetState(ZombieAnimState::DIE);
    }
    else if (m_IsJumping) {
        m_AnimController.SetState(ZombieAnimState::JUMP);
    }
    else if (m_IsAttacking) {
        m_AnimController.SetState(ZombieAnimState::ATTACK);
    }
    else if (m_HasPole) {
        m_AnimController.SetState(ZombieAnimState::RUN);
    }
    else {
        m_AnimController.SetState(ZombieAnimState::WALK);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}