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

std::shared_ptr<Util::Animation> AnimationFactory::CreateSnowPeaIdle() {
    std::vector<std::string> paths;
    for (int i = 0; i <= 14; ++i) { // 根據你的檔案 SnowPea_0 ~ SnowPea_14
        paths.push_back(RESOURCE_DIR "/graphics/Plants/SnowPea/SnowPea_" + std::to_string(i) + ".png");
    }
    return std::make_shared<Util::Animation>(paths, true, 100); // 100ms 間隔
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateCherryBombExplode() {
    std::vector<std::string> paths;
    for (int i = 0; i <= 6; ++i) { // 根據資源檔 CherryBomb_0 ~ CherryBomb_6
        paths.push_back(RESOURCE_DIR "/graphics/Plants/CherryBomb/CherryBomb_" + std::to_string(i) + ".png");
    }
    // 設定不循環(false)，因為炸完就消失
    return std::make_shared<Util::Animation>(paths, false, 100);
}

std::shared_ptr<Util::Animation> AnimationFactory::CreateZombieBoomDie() {
    std::vector<std::string> paths;

    // 指向你指定的新圖片路徑
    // 假設你將該圖片命名為 BoomDie_0.png 放在這個目錄下
    for (int i = 0; i <= 20; ++i)
    {
        // 根據資源檔 CherryBomb_0 ~ CherryBomb_6
        paths.push_back(RESOURCE_DIR "/graphics/Zombies/zm_dead"+ std::to_string(i) + ".png");
    }
    // 因為只有一張圖，時間間隔設長一點也沒關係，false 代表不循環
    return std::make_shared<Util::Animation>(paths, false, 100);
}