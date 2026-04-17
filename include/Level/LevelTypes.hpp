//
// Created by hankl on 2026/4/5.
//

#ifndef LEVELTYPES_HPP
#define LEVELTYPES_HPP

#include "pch.hpp"

enum class LevelMode {
    NORMAL,
    BOWLING
};

enum class ZombieType {
    BASIC,
    CONEHEAD
};

enum class PlantType {
    PEASHOOTER,
    SUNFLOWER,
    CHERRY_BOMB,
    WALLNUT,
    POTATO_MINE,
    SNOW_PEA,
    CHOMPER,
    REPEATER_PEA
};

enum class ProjectileType {
    PEA,
    SNOW_PEA
};

enum class BoardTypes {
    DAY_SINGLE_ROW,
    DAY_MIDDLE_3_ROW,
    DAY_FULL_5_ROW
};

#endif //LEVELTYPES_HPP
