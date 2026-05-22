#include "Entity/PeaIce.hpp"

PeaIce::PeaIce(int row, const glm::vec2& position)
    : Projectile(
        RESOURCE_DIR "/graphics/Bullets/PeaIce/PeaIce_0.png",
        row,
        position,
        1,
        220.0f) {
}

void PeaIce::Update() {
    Projectile::Update();
}

bool PeaIce::AppliesSlowEffect() const {
    return true;
}
