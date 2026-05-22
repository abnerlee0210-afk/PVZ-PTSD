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
    ATTACK,
    DIE,
    BOOM_DIE,
};

class Zombie : public Util::GameObject {
public:
    Zombie(const std::string& imagePath,
           int row,
           const glm::vec2& position,
           int hp,
           float speed);

    virtual ~Zombie() = default;

    virtual void Update();

    // 核心受傷多載：只保留這一個帶有預設值的虛擬函式，解決二義性
    virtual void TakeDamage(int damage, bool isExplosion = false);

    int GetRow() const { return m_Row; }
    int GetHP() const { return m_HP; }
    float GetSpeed() const { return m_Speed; }
    bool IsAlive() const { return m_Alive; }
    bool IsSlowed() const { return m_IsSlowed; }
    bool IsBoomDying() const;
    bool IsDeathAnimationFinished() const;

    bool CanAttack() const;
    void ResetAttackTimer();

    // 【已修正】將大括號完整閉合
    void SetAttacking(bool attacking) { m_IsAttacking = attacking; }
    bool IsAttacking() const { return m_IsAttacking; }

    void SlowDown(float duration);

    virtual void InitAnimations() {}
    void UpdateAnimationState();

protected:
    int m_Row;
    int m_HP;
    float m_Speed;
    bool m_Alive;

    float m_AttackTimer;
    float m_AttackInterval;
    bool m_IsAttacking;

    // 寒冰減速機制變數
    bool m_IsSlowed = false;
    float m_SlowTimer = 0.0f;

    AnimationStateController<ZombieAnimState> m_AnimController;

private:
    void ApplySlowColor();
    void ClearSlow();
};

#endif //ZOMBIE_HPP
