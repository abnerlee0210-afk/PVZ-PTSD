//
// Created by hankl on 2026/4/5.
//
#include "Level/LevelRepository.hpp"

LevelConfig LevelRepository::GetLevel(int levelId) {
    switch (levelId) {
        case 1:
            return CreateLevel1();
        case 2:
            return CreateLevel2();
        default:
            return CreateLevel1();
    }
}

LevelConfig LevelRepository::CreateLevel1() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_0.jpg";

    level.levelId = 1;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_SINGLE_ROW;

    level.rows = 1;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 150;

    level.hasSkySun = true;
    level.hasShovel = false;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {0};

    level.allowedPlants = {
        PlantType::PEASHOOTER
    };

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, 0, 18.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::BASIC, 0, 30.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::BASIC, 0, 42.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::BASIC, 0, 54.0f},
        {ZombieType::BASIC, 0, 55.0f}
    };

    level.waves = {wave1, wave2, wave3, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel2() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_1.jpg";

    level.levelId = 2;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_MIDDLE_3_ROW;

    level.rows = 3;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.hasSkySun = true;
    level.hasShovel = false;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {0,1,2};

    level.allowedPlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER
    };

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 18.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::BASIC, -1, 38.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::BASIC, -1, 45.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BASIC, -1, 60.0f},
        {ZombieType::BASIC, -1, 61.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::BASIC, -1, 75.0f},
        {ZombieType::BASIC, -1, 76.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::BASIC, -1, 95.0f},
        {ZombieType::BASIC, -1, 98.0f},
        {ZombieType::BASIC, -1, 98.0f},
        {ZombieType::BASIC, -1, 100.0f},
        {ZombieType::BASIC, -1, 100.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, finalWave};

    return level;
}

