//
// Created by hankl on 2026/4/8.
//
#include "Factory/PlantFactory.hpp"

#include "Entity/Plant/Peashooter.hpp"
#include "Entity/Plant/Sunflower.hpp"
#include "Entity/Plant/CherryBomb.hpp"
#include "Entity/Plant//WallNut.hpp"
#include "Entity/Plant/PotatoMine.hpp"
#include "Entity/Plant/SnowPeashooter.hpp"
#include "Entity/Plant/RepeaterPea.hpp"
#include "Entity/Plant/Chomper.hpp"

std::shared_ptr<Plant> PlantFactory::CreatePlant(
    PlantType type,
    int row,
    int col,
    const glm::vec2& position
) {
    switch (type) {
        case PlantType::PEASHOOTER:
            return std::make_shared<Peashooter>(row, col, position);

        case PlantType::SUNFLOWER:
            return std::make_shared<Sunflower>(row, col, position);

        case PlantType::CHERRY_BOMB:
            return std::make_shared<CherryBomb>(row, col, position);

        case PlantType::WALL_NUT:
            return std::make_shared<WallNut>(row, col, position);

        case PlantType::POTATO_MINE:
            return std::make_shared<PotatoMine>(row, col, position);

        case PlantType::SNOW_PEASHOOTER:
            return std::make_shared<SnowPeashooter>(row, col, position);
        case PlantType::REPEATER_PEA:
            return std::make_shared<RepeaterPea>(row, col, position);
        case PlantType::CHOMPER:
            return std::make_shared<Chomper>(row, col, position);
        default:
            return nullptr;
    }
}

int PlantFactory::GetCost(PlantType type) {
    switch (type) {
        case PlantType::PEASHOOTER:
            return 100;

        case PlantType::SUNFLOWER:
            return 50;

        case PlantType::CHERRY_BOMB:
            return 150;

        case PlantType::WALL_NUT:
            return 50;

        case PlantType::POTATO_MINE:
            return 25;

        case PlantType::SNOW_PEASHOOTER:
            return 175;

        case PlantType::CHOMPER:
            return 150;

        case PlantType::REPEATER_PEA:
            return 200;

        default:
            return 9999;
    }
}