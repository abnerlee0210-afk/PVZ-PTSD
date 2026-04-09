//
// Created by hankl on 2026/4/5.
//

#ifndef LEVELCONFIG_HPP
#define LEVELCONFIG_HPP

#include "pch.hpp"

#include "Level/LevelTypes.hpp"

struct SpawnEvent {
    ZombieType type;
    int row;
    float spawnTime;
    bool spawned = false;
};

struct Wave {
    std::vector<SpawnEvent> events;
    bool isFinalWave = false;
};

struct LevelConfig {
    int levelId = 1;
    LevelMode mode = LevelMode::NORMAL;

    int rows = 5;
    int cols = 9;

    float startX = -460.0f;
    float startY = -270.0f;

    std::string backgroundPath;

    int initialSun = 50;

    bool hasSkySun = true;
    bool hasShovel = true;
    bool hasLawnMowers = true;

    float introPanDuration = 5.0f;
    float readySetPlantDuration = 2.0f;
    float firstZombieDelay = 18.0f;

    float skySunMinInterval = 5.0f;
    float skySunMaxInterval = 7.0f;
    float sunLifeTime = 8.0f;

    std::vector<int> lawnMowerRows;
    std::vector<PlantType> allowedPlants;
    std::vector<Wave> waves;
};

#endif //LEVELCONFIG_HPP
