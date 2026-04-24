//
// Created by hankl on 2026/4/24.
//
#include "Factory/AnimationFactory.hpp"

std::shared_ptr<Util::Animation> AnimationFactory::CreateBasicZombieWalk() {
    std::vector<std::string> paths;
    paths.reserve(22); // 預分配記憶體提升效能

    for (int i = 0; i <= 21; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Zombies/NormalZombie/Zombie/Zombie_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreatePeashooterIdle() {
    std::vector<std::string> paths;
    paths.reserve(22); // 預分配記憶體提升效能

    for (int i = 0; i <= 12; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/Peashooter/Peashooter_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateSunflowerIdle() {
    std::vector<std::string> paths;
    paths.reserve(22); // 預分配記憶體提升效能

    for (int i = 0; i <= 17; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/SunFlower/SunFlower_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}