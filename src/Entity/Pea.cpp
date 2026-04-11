//
// Created by hankl on 2026/3/10.
//
#include "Entity/Pea.hpp"

Pea::Pea(int row, const glm::vec2& position)
    : Projectile(RESOURCE_DIR "/graphics/Bullets/PeaNormal/PeaNormal_0.png",
        row,
        position,
        1,
        220.0f) {
}

void Pea::Update() {
    Projectile::Update();
}