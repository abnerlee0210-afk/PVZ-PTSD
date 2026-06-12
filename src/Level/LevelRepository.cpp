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
        case 3:
            return CreateLevel3();
        case 4:
            return CreateLevel4();
        case 5:
            return CreateLevel5();
        case 6:
            return CreateLevel6();
        case 7:
            return CreateLevel7();
        case 8:
            return CreateLevel8();
        case 9:
            return CreateLevel9();
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

    level.initialSun = 50;

    level.needChoosePlants = false;

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

    level.needChoosePlants = false;

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

LevelConfig LevelRepository::CreateLevel3() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_1.jpg";

    level.levelId = 3;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_MIDDLE_3_ROW;

    level.rows = 3;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = false;

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
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
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
        {ZombieType::BASIC, -1, 50.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BASIC, -1, 65.0f},
        {ZombieType::BASIC, -1, 67.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::CONEHEAD, -1, 80.0f}
    };

    Wave wave6;
    wave6.isFinalWave = false;
    wave6.events = {
        {ZombieType::CONEHEAD, -1, 95.0f}
    };

    Wave wave7;
    wave7.isFinalWave = false;
    wave7.events = {
        {ZombieType::BASIC, -1, 110.0f},
        {ZombieType::CONEHEAD, -1, 112.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::BASIC, -1, 132.0f},
        {ZombieType::BASIC, -1, 132.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::CONEHEAD, -1, 138.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, wave6, wave7, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel4() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 4;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = false;

    level.hasSkySun = true;
    level.hasShovel = false;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {0,1,2,3,4};

    level.allowedPlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
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
        {ZombieType::BASIC, -1, 50.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BASIC, -1, 65.0f},
        {ZombieType::BASIC, -1, 67.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::CONEHEAD, -1, 80.0f}
    };

    Wave wave6;
    wave6.isFinalWave = false;
    wave6.events = {
        {ZombieType::CONEHEAD, -1, 95.0f}
    };

    Wave wave7;
    wave7.isFinalWave = false;
    wave7.events = {
        {ZombieType::BASIC, -1, 110.0f},
        {ZombieType::CONEHEAD, -1, 112.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::BASIC, -1, 132.0f},
        {ZombieType::BASIC, -1, 132.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::BASIC, -1, 134.0f},
        {ZombieType::CONEHEAD, -1, 138.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, wave6, wave7, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel5() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 5;
    level.mode = LevelMode::BOWLING;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = false;

    level.hasSkySun = true;
    level.hasShovel = true;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {1,2,3};

    level.allowedPlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
        PlantType::POTATO_MINE
    };

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 20.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::BASIC, -1, 38.0f},
        {ZombieType::BASIC, -1, 42.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::CONEHEAD, -1, 58.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BASIC, -1, 72.0f},
        {ZombieType::BASIC, -1, 75.0f},
        {ZombieType::CONEHEAD, -1, 80.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::BASIC, -1, 96.0f},
        {ZombieType::CONEHEAD, -1, 100.0f},
        {ZombieType::BASIC, -1, 104.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::FLAG, -1, 120.0f},
        {ZombieType::BASIC, -1, 121.0f},
        {ZombieType::BASIC, -1, 122.0f},
        {ZombieType::CONEHEAD, -1, 124.0f},
        {ZombieType::BASIC, -1, 126.0f},
        {ZombieType::CONEHEAD, -1, 130.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel6() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 6;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = false;

    level.hasSkySun = true;
    level.hasShovel = true;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {1,2,3};

    level.allowedPlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
        PlantType::POTATO_MINE
    };

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 20.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::BASIC, -1, 38.0f},
        {ZombieType::BASIC, -1, 42.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::CONEHEAD, -1, 58.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BASIC, -1, 72.0f},
        {ZombieType::BASIC, -1, 75.0f},
        {ZombieType::CONEHEAD, -1, 80.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::BASIC, -1, 96.0f},
        {ZombieType::CONEHEAD, -1, 100.0f},
        {ZombieType::BASIC, -1, 104.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::FLAG, -1, 120.0f},
        {ZombieType::BASIC, -1, 121.0f},
        {ZombieType::BASIC, -1, 122.0f},
        {ZombieType::CONEHEAD, -1, 124.0f},
        {ZombieType::BASIC, -1, 126.0f},
        {ZombieType::CONEHEAD, -1, 130.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel7() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 7;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = false;

    level.hasSkySun = true;
    level.hasShovel = true;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {1,2,3};

    level.allowedPlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
        PlantType::POTATO_MINE,
        PlantType::SNOW_PEASHOOTER,
    };

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 20.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::POLE_VAULTING, -1, 40.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::BASIC, -1, 56.0f},
        {ZombieType::CONEHEAD, -1, 60.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::POLE_VAULTING, -1, 76.0f},
        {ZombieType::BASIC, -1, 80.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::CONEHEAD, -1, 96.0f},
        {ZombieType::POLE_VAULTING, -1, 100.0f}
    };

    Wave wave6;
    wave6.isFinalWave = false;
    wave6.events = {
        {ZombieType::BASIC, -1, 112.0f},
        {ZombieType::BASIC, -1, 114.0f},
        {ZombieType::POLE_VAULTING, -1, 118.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::FLAG, -1, 138.0f},
        {ZombieType::POLE_VAULTING, -1, 139.0f},
        {ZombieType::BASIC, -1, 140.0f},
        {ZombieType::CONEHEAD, -1, 142.0f},
        {ZombieType::POLE_VAULTING, -1, 145.0f},
        {ZombieType::BASIC, -1, 146.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, wave6, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel8() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 8;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = true;
    level.maxChoosePlants = 6;

    level.hasSkySun = true;
    level.hasShovel = true;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {1,2,3};

    level.availablePlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
        PlantType::POTATO_MINE,
        PlantType::SNOW_PEASHOOTER,
        PlantType::REPEATER_PEA
    };

    level.allowedPlants = {};

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 22.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::CONEHEAD, -1, 42.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::BASIC, -1, 58.0f},
        {ZombieType::BASIC, -1, 62.0f},
        {ZombieType::POLE_VAULTING, -1, 66.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BUCKETHEAD, -1, 84.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::CONEHEAD, -1, 100.0f},
        {ZombieType::BASIC, -1, 102.0f},
        {ZombieType::POLE_VAULTING, -1, 106.0f}
    };

    Wave wave6;
    wave6.isFinalWave = false;
    wave6.events = {
        {ZombieType::BUCKETHEAD, -1, 120.0f},
        {ZombieType::BASIC, -1, 123.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::FLAG, -1, 145.0f},
        {ZombieType::BASIC, -1, 146.0f},
        {ZombieType::CONEHEAD, -1, 147.0f},
        {ZombieType::POLE_VAULTING, -1, 149.0f},
        {ZombieType::BUCKETHEAD, -1, 152.0f},
        {ZombieType::BASIC, -1, 154.0f},
        {ZombieType::CONEHEAD, -1, 156.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, wave6, finalWave};

    return level;
}

LevelConfig LevelRepository::CreateLevel9() {
    LevelConfig level;

    level.backgroundPath = RESOURCE_DIR "/graphics/Items/Background/Background_2.jpg";

    level.levelId = 9;
    level.mode = LevelMode::NORMAL;

    level.boardTypes = BoardTypes::DAY_FULL_5_ROW;

    level.rows = 5;
    level.cols = 9;

    level.startY = -70.0f;

    level.initialSun = 50;

    level.needChoosePlants = true;
    level.maxChoosePlants = 6;

    level.hasSkySun = true;
    level.hasShovel = true;
    level.hasLawnMowers = true;

    level.introPanDuration = 5.0f;
    level.readySetPlantDuration = 2.0f;
    level.firstZombieDelay = 18.0f;

    level.skySunMinInterval = 5.0f;
    level.skySunMaxInterval = 7.0f;
    level.sunLifeTime = 8.0f;

    level.lawnMowerRows = {1,2,3};

    level.availablePlants = {
        PlantType::PEASHOOTER,
        PlantType::SUNFLOWER,
        PlantType::CHERRY_BOMB,
        PlantType::WALL_NUT,
        PlantType::POTATO_MINE,
        PlantType::SNOW_PEASHOOTER,
        PlantType::REPEATER_PEA,
        PlantType::CHOMPER
    };

    level.allowedPlants = {};

    Wave wave1;
    wave1.isFinalWave = false;
    wave1.events = {
        {ZombieType::BASIC, -1, 22.0f}
    };

    Wave wave2;
    wave2.isFinalWave = false;
    wave2.events = {
        {ZombieType::CONEHEAD, -1, 42.0f},
        {ZombieType::BASIC, -1, 46.0f}
    };

    Wave wave3;
    wave3.isFinalWave = false;
    wave3.events = {
        {ZombieType::POLE_VAULTING, -1, 62.0f}
    };

    Wave wave4;
    wave4.isFinalWave = false;
    wave4.events = {
        {ZombieType::BUCKETHEAD, -1, 82.0f}
    };

    Wave wave5;
    wave5.isFinalWave = false;
    wave5.events = {
        {ZombieType::BASIC, -1, 98.0f},
        {ZombieType::CONEHEAD, -1, 101.0f},
        {ZombieType::POLE_VAULTING, -1, 105.0f}
    };

    Wave wave6;
    wave6.isFinalWave = false;
    wave6.events = {
        {ZombieType::BUCKETHEAD, -1, 120.0f},
        {ZombieType::BASIC, -1, 123.0f},
        {ZombieType::CONEHEAD, -1, 126.0f}
    };

    Wave wave7;
    wave7.isFinalWave = false;
    wave7.events = {
        {ZombieType::POLE_VAULTING, -1, 138.0f},
        {ZombieType::BASIC, -1, 140.0f},
        {ZombieType::BASIC, -1, 142.0f}
    };

    Wave finalWave;
    finalWave.isFinalWave = true;
    finalWave.events = {
        {ZombieType::FLAG, -1, 160.0f},
        {ZombieType::BASIC, -1, 161.0f},
        {ZombieType::CONEHEAD, -1, 162.0f},
        {ZombieType::POLE_VAULTING, -1, 164.0f},
        {ZombieType::BUCKETHEAD, -1, 166.0f},
        {ZombieType::BUCKETHEAD, -1, 170.0f},
        {ZombieType::CONEHEAD, -1, 172.0f},
        {ZombieType::BASIC, -1, 174.0f}
    };

    level.waves = {wave1, wave2, wave3, wave4, wave5, wave6, wave7, finalWave};

    return level;
}