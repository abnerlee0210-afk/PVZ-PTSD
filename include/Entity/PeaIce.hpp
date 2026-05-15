#ifndef PEAICE_HPP
#define PEAICE_HPP

#include "Entity/Pea.hpp"

class PeaIce : public Pea {
public:
    // 根據父類 Projectile 的要求傳入參數
    PeaIce(int row, const glm::vec2& position)
        : Pea(row, position) {

        // 1. 更換貼圖為寒冰豌豆
        m_Drawable = std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Bullets/PeaIce/PeaIce_0.png");

        // 2. 設定寒冰傷害屬性（如果需要與普通豌豆不同）
        m_Damage = 20;
    }

    // 這裡很重要：讓系統知道這顆子彈的類型是 SNOW_PEA，以便在 GameBoard 處理減速
    // 如果你的 Pea.hpp 有 GetType，請覆寫它
};

#endif