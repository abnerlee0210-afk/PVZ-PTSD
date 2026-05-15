#include "Entity/Zombie.hpp"
#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp" // 必須包含

Zombie::Zombie(const std::string& imagePath,
               int row,
               const glm::vec2& position,
               int hp,
               float speed)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), 10.0f),
      m_Row(row),
      m_HP(hp), // 統一使用 m_HP
      m_Speed(speed),
      m_Alive(true),
      m_AttackTimer(0.0f),
      m_AttackInterval(1.0f),
      m_IsAttacking(false),
      m_IsSlowed(false),
      m_SlowTimer(0.0f) {
    m_Transform.translation = position;
}

void Zombie::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }

    const float deltaTime = Util::Time::GetDeltaTimeMs() / 1000.0f;

    // 1. 處理減速計時與倍率
    float speedMultiplier = 1.0f;
    if (m_IsSlowed) {
        speedMultiplier = 0.5f;
        m_SlowTimer -= deltaTime;
        if (m_SlowTimer <= 0) {
            m_IsSlowed = false;
        }
    }

    // 2. 移動邏輯 (合併減速倍率)
    if (m_IsAttacking) {
        m_AttackTimer += deltaTime;
    } else {
        // 確保將 speedMultiplier 乘進去
        m_Transform.translation.x -= (m_Speed * speedMultiplier) * deltaTime;
    }

    UpdateAnimationState();
}

// 合併後的 TakeDamage，支援普通受傷與爆炸焦黑效果
void Zombie::TakeDamage(int damage, bool isExplosion) {
    if (!m_Alive) return;

    m_HP -= damage; // 統一使用 m_HP

    if (m_HP <= 0) {
        m_HP = 0;
        m_Alive = false;

        if (isExplosion) {
            // 切換到焦黑死亡動畫
            m_Speed = 0; // 停止移動
            auto boomAnim = AnimationFactory::CreateZombieBoomDie();
            // 直接取代目前的動畫狀態或手動 Set
            m_AnimController.AddAnimation(ZombieAnimState::DIE, boomAnim);
            m_AnimController.SetState(ZombieAnimState::DIE);
            SetDrawable(boomAnim);
        } else {
            // 普通死亡邏輯...
            m_AnimController.SetState(ZombieAnimState::DIE);
        }
    }
}

bool Zombie::CanAttack() const {
    return m_AttackTimer >= m_AttackInterval;
}

void Zombie::ResetAttackTimer() {
    m_AttackTimer = 0.0f;
}

void Zombie::SlowDown(float duration) {
    m_IsSlowed = true;
    m_SlowTimer = duration;
}

void Zombie::UpdateAnimationState() {
    if (!m_Alive) {
        m_AnimController.SetState(ZombieAnimState::DIE);
    }
    else if (m_IsAttacking) {
        m_AnimController.SetState(ZombieAnimState::ATTACK);
    }
    else {
        m_AnimController.SetState(ZombieAnimState::WALK);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}