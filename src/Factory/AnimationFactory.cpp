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

std::shared_ptr<Util::Animation> AnimationFactory::CreateConeheadZombieWalk() {
    std::vector<std::string> paths;
    paths.reserve(21);

    for (int i = 0; i <= 20; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Zombies/ConeheadZombie/coneheadZombie/ConeheadZombie_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateSunIdle() {
    std::vector<std::string> paths;
    paths.reserve(22);

    for (int i = 0; i <= 21; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/Sun/Sun_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreatePeashooterIdle() {
    std::vector<std::string> paths;
    paths.reserve(13);

    for (int i = 0; i <= 12; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/Peashooter/Peashooter_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateSunflowerIdle() {
    std::vector<std::string> paths;
    paths.reserve(18);

    for (int i = 0; i <= 17; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/SunFlower/SunFlower_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

// ===========================================================
// WallNut
// ===========================================================

std::shared_ptr<Util::Animation> AnimationFactory::CreateWallNutComplete() {
    std::vector<std::string> paths;
    paths.reserve(16);

    for (int i = 0; i <= 15; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/WallNut/WallNut/WallNut_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateWallNutCracked1() {
    std::vector<std::string> paths;
    paths.reserve(11);

    for (int i = 0; i <= 10; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/WallNut/WallNut_cracked1/WallNut_cracked1_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateWallNutCracked2() {
    std::vector<std::string> paths;
    paths.reserve(15);

    for (int i = 0; i <= 14; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Plants/WallNut/WallNut_cracked2/WallNut_cracked2_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

// ===================================================
// Zombie Attack
// ===================================================
std::shared_ptr<Util::Animation> AnimationFactory::CreateBasicZombieAttack() {
    std::vector<std::string> paths;
    paths.reserve(21);

    for (int i = 0; i <= 20; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Zombies/NormalZombie/ZombieAttack/ZombieAttack_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateConeheadZombieAttack() {
    std::vector<std::string> paths;
    paths.reserve(11);

    for (int i = 0; i <= 10; ++i) {
        paths.push_back(RESOURCE_DIR "/graphics/Zombies/ConeheadZombie/ConeheadZombieAttack/ConeheadZombieAttack_" + std::to_string(i) + ".png");
    }

    return std::make_shared<Util::Animation>(paths, true, 100, true, 0);
}

