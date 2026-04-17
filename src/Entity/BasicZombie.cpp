//
// Created by hankl on 2026/3/10.
//
#include "Entity/BasicZombie.hpp"

BasicZombie::BasicZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/NormalZombie/Zombie/Zombie_0.png",
        row,
        position,
        12,
        18.0f) {
}

void BasicZombie::Update() {
    Zombie::Update();
}