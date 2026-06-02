//
// Created by hankl on 2026/3/10.
//

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Animation/AnimationStateController.hpp"

enum class ZombieAnimState {
    WALK,
    RUN, // For PoleVaultingZombie
    JUMP, // For PoleVaultingZombie
    ATTACK,
    DIE
};

class Zombie : public Util::GameObject {
public:
    Zombie(const std::string& imagePath,
           int row,
           const glm::vec2& position,
           int hp,
           int ad,
           float speed);

    virtual ~Zombie() = default;

    virtual void Update();
    virtual void TakeDamage(int damage);

    int GetRow() const { return m_Row; }
    int GetHP() const { return m_HP; }
    int GetAD() const { return m_AD; }
    float GetSpeed() const { return m_Speed; }
    bool IsAlive() const { return m_Alive; }
    bool ShouldRemove() const { return m_ShouldRemove; }

    float GetCollisionRadius() const { return m_CollisionRadius; }
    float GetAttackRange() const { return m_AttackRange; }

    bool CanAttack() const;
    void ResetAttackTimer();
    void SetAttacking(bool attacking) {m_IsAttacking = attacking;}
    bool IsAttacking() const {return m_IsAttacking;}

    virtual bool CanJumpOverPlant() const { return false; }
    virtual void StartJumpOverPlant(const glm::vec2& plantPos) {}
    virtual bool IsJumping() const { return false; }

    void ApplySlow();
    bool IsSlowed() const { return m_IsSlowed; }

    void UpdateZIndexByY();

    virtual void InitAnimations(){}
    virtual void UpdateAnimationState();

protected:
    int m_Row;
    int m_HP;
    int m_AD;
    float m_Speed;
    bool m_Alive;

    float m_AttackTimer;
    float m_AttackInterval;
    bool m_IsAttacking;

    float m_BaseSpeed;
    bool m_IsSlowed;
    float m_SlowTimer;
    float m_SlowDuration;

    float m_CollisionRadius = 20.0f;
    float m_AttackRange = 20.0f;

    bool m_IsDying = false;
    bool m_ShouldRemove = false;

    float m_DieTimer = 0.0f;
    float m_DieDuration = 0.8f;

    AnimationStateController<ZombieAnimState> m_AnimController;
};

#endif //ZOMBIE_HPP