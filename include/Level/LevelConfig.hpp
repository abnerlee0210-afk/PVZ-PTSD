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

    BoardTypes boardTypes = BoardTypes::DAY_FULL_5_ROW;

    float boundariesX = 512.0f;
    float CameraOffset = 190.0f;
    float WorldPos = 190.0f;

    float startX = -270;
    float startY = -270.0f;
    float m_HomeLineX = startX - 10.0f; // 用於判定殭屍是否走進家裡

    float SpawnZombiePosXBias = 80.0f ;

    glm::vec2 BackgroundPos = glm::vec2(190.0f,0.0f);
    glm::vec2 SeedChooserPos = glm::vec2(-170.0f, 260.0f);

    std::string fontDir = RESOURCE_DIR "/font.ttf";
    std::string VictoryScreenPath = RESOURCE_DIR "/graphics/Screen/GameVictory.png";
    std::string LooseScreenPath = RESOURCE_DIR "/graphics/Screen/GameLoose.png";

    std::string backgroundPath;

    int initialSun = 50;

    bool hasSkySun = true;
    bool hasShovel = true;
    bool hasLawnMowers = true;

    float introPanDuration = 5.0f;
    float readySetPlantDuration = 2.0f;
    float firstZombieDelay = 18.0f;

    float skySunMinInterval = 4.0f;
    float skySunMaxInterval = 8.0f;
    float sunLifeTime = 12.0f;



    std::vector<int> lawnMowerRows;
    std::vector<PlantType> allowedPlants;
    std::vector<Wave> waves;
};

#endif //LEVELCONFIG_HPP
