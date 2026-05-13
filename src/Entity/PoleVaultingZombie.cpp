//
// Created by 李政翰 on 2026/5/13.
//
#include "Entity/PoleVaultingZombie.hpp"

#include "Util/Time.hpp"

PoleVaultingZombie::PoleVaultingZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/FlagZombie/FlagZombie/FlagZombie_0.png",
        row,
        position,
        100,
        70.0f
    ) {
    m_Speed = m_PoleSpeed;
}

void PoleVaultingZombie::Update() {
    if (!m_Alive) {
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

        // 簡單跳躍弧線：中間往上
        float jumpHeight = 45.0f;
        float arc = 4.0f * t * (1.0f - t);
        m_Transform.translation.y =
            m_JumpStartPos.y + (m_JumpTargetPos.y - m_JumpStartPos.y) * t + jumpHeight * arc;

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
    m_JumpTargetPos.x -= 80.0f;
}