#include "Entity/Zombie.hpp"
#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"

#include <algorithm>

Zombie::Zombie(const std::string& imagePath,
               int row,
               const glm::vec2& position,
               int hp,
               float speed)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), 10.0f),
      m_Row(row),
      m_HP(hp),
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
            ClearSlow();
        }
    }

    // 2. 移動邏輯 (合併減速倍率)
    if (m_IsAttacking) {
        m_AttackTimer += deltaTime;
    } else {
        m_Transform.translation.x -= (m_Speed * speedMultiplier) * deltaTime;
    }

    UpdateAnimationState();
}

// 合併後的 TakeDamage，支援普通受傷與爆炸焦黑效果
void Zombie::TakeDamage(int damage, bool isExplosion) {
    if (!m_Alive) return;

    m_HP -= damage;

    if (m_HP <= 0) {
        m_HP = 0;
        m_Alive = false;
        m_IsAttacking = false;
        ClearSlow();

        if (isExplosion) {
            // 1. 停止移動
            m_Speed = 0.0f;

            // 2. 建立焦黑靜態圖/動畫
            auto boomAnim = AnimationFactory::CreateZombieBoomDie();

            // 3. 註冊並切換至對應的 BOOM_DIE 狀態
            m_AnimController.AddAnimation(ZombieAnimState::BOOM_DIE, boomAnim);
            m_AnimController.SetState(ZombieAnimState::BOOM_DIE);

            // 4. 更換顯示圖片
            SetDrawable(boomAnim);
        } else {
            // 普通死亡邏輯
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
    if (!m_Alive || duration <= 0.0f) {
        return;
    }

    m_IsSlowed = true;
    m_SlowTimer = std::max(m_SlowTimer, duration);
    ApplySlowColor();
}

bool Zombie::IsBoomDying() const {
    return m_AnimController.GetState() == ZombieAnimState::BOOM_DIE;
}

bool Zombie::IsDeathAnimationFinished() const {
    auto anim = m_AnimController.GetCurrentAnimation();
    if (!anim) {
        return true;
    }

    return anim->GetState() == Util::Animation::State::ENDED;
}

void Zombie::ApplySlowColor() {
    SetColor(glm::vec4{0.45f, 0.70f, 1.0f, 1.0f});
}

void Zombie::ClearSlow() {
    m_IsSlowed = false;
    m_SlowTimer = 0.0f;
    SetColor(glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
}

void Zombie::UpdateAnimationState() {
    // 如果已經在爆炸死亡狀態，交由 TakeDamage 手動更換的圖片控制，不強制複寫
    auto currentState = m_AnimController.GetState(); // 假設控制器有 GetState()
    if (currentState == ZombieAnimState::BOOM_DIE) {
        return;
    }

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
