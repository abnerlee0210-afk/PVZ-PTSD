#include "Entity/CherryBomb.hpp"
#include "Util/Time.hpp"
#include "Factory/AnimationFactory.hpp"

CherryBomb::CherryBomb(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/CherryBomb/CherryBomb_0.png",
        row, col, position,
        150, // 陽光花費
        300  // 生命值
    ),
      m_ExplodeTimer(0.0f),
      m_ExplodeDelay(0.6f), // 預留一點點動畫閃爍時間
      m_Exploded(false) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::IDLE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void CherryBomb::Update() {
    if (!m_Alive) return;

    m_ExplodeTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;

    if (m_ExplodeTimer >= m_ExplodeDelay && !m_Exploded) {
        m_Exploded = true;
        // 標記為死亡，讓 GameBoard 處理爆炸後移除
        m_Alive = false; 
    }
    
    UpdateAnimationState();
}

void CherryBomb::InitAnimations() {
    // 這裡需要去 AnimationFactory 新增 CreateCherryBomb 方法
    auto explodeAnim = AnimationFactory::CreateCherryBombExplode();
    m_AnimController.AddAnimation(PlantAnimState::IDLE, explodeAnim);
}