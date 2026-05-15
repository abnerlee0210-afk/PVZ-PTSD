#include "Entity/SnowPea.hpp"
#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"

SnowPea::SnowPea(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/SnowPea/SnowPea_0.png",
        row, col, position,
        175, // 陽光花費
        300  // 生命值
    ),
      m_ShootInterval(1.5f), // 調整順序：Interval 在 Timer 之前
      m_ShootTimer(0.0f)
{
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void SnowPea::Update() {
    if (!m_Alive) {
        UpdateAnimationState();
        return;
    }
    // 累加時間
    m_ShootTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    UpdateAnimationState();
}

bool SnowPea::CanShoot() const {
    return m_ShootTimer >= m_ShootInterval;
}

ProjectileType SnowPea::GetProjectileType() const {
    return ProjectileType::SNOW_PEA; // 返回冰豆類型
}

glm::vec2 SnowPea::GetProjectileSpawnPosition() const {
    glm::vec2 pos = m_Transform.translation;
    pos.x += 30.0f; // 讓子彈從炮口射出
    return pos;
}

void SnowPea::ResetShootTimer() {
    m_ShootTimer = 0.0f;
}

void SnowPea::InitAnimations() {
    // 呼叫你在 AnimationFactory 新增的方法
    auto idle = AnimationFactory::CreateSnowPeaIdle(); 
    m_AnimController.AddAnimation(PlantAnimState::IDLE, idle);
    m_AnimController.AddAnimation(PlantAnimState::ATTACK, idle);
    m_AnimController.AddAnimation(PlantAnimState::DIE, idle);
}