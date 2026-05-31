//
// Created by 李政翰 on 2026/5/13.
//

#ifndef POLEVAULTINGZOMBIE_HPP
#define POLEVAULTINGZOMBIE_HPP

#include "Zombie.hpp"

class PoleVaultingZombie : public Zombie {
public:
    PoleVaultingZombie(int row, const glm::vec2& position);

    void Update() override;

    bool CanJumpOverPlant() const override;
    void StartJumpOverPlant(const glm::vec2& plantPos) override;
    bool IsJumping() const override { return m_IsJumping; }

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;

private:
    bool m_HasPole = true;
    bool m_IsJumping = false;

    float m_JumpTimer = 0.0f;
    float m_JumpDuration = 0.45f;

    glm::vec2 m_JumpStartPos;
    glm::vec2 m_JumpTargetPos;

    float m_NormalSpeed = 18.0f;
    float m_PoleSpeed = 30.0f;

};

#endif // POLEVAULTINGZOMBIE_HPP