//
// Created by LAB1223 on 2026/5/29.
//
#include "Entity/Projectile/SnowPea.hpp"

SnowPeaProjectile::SnowPeaProjectile(int row, const glm::vec2& position)
    : Projectile(
        RESOURCE_DIR "/graphics/Bullets/PeaIce/PeaIce_0.png",
        row,
        position,
        1,
        250.0f
    ) {
}

bool SnowPeaProjectile::CanSlow() const {
    return true;
}