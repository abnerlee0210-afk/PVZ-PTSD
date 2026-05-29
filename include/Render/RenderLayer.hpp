//
// Created by 李政翰 on 2026/5/29.
//

#ifndef RENDERLAYER_HPP
#define RENDERLAYER_HPP

namespace RenderLayer {
    constexpr float BACKGROUND = -10.0f;

    // World
    constexpr float PLANT_BASE = 10.0f;
    constexpr float ZOMBIE_BASE = 10.0f;
    constexpr float LAWN_MOWER_BASE = 20.0f;

    constexpr float PROJECTILE = 40.0f;
    constexpr float SUN = 50.0f;
    constexpr float EFFECT = 60.0f;

    // UI
    constexpr float LEVEL_CARD = 70.0f;
    constexpr float SEED_CARD = 80.0f;
    constexpr float COOLDOWN_OVERLAY = 90.0f;
    constexpr float COOLDOWN_TEXT = 99.0f;
    constexpr float OUTER_FRAME = 100.0f;

    constexpr float UI = 120.0f;
    constexpr float UI_OVERLAY = 150.0f;
    constexpr float END_SCREEN = 100.0f;

    constexpr float Y_SORT_FACTOR = 0.1f;

    inline float WorldYSort(float baseZ, float y) {
        return baseZ - y * Y_SORT_FACTOR;
    }
}

#endif //RENDERLAYER_HPP
