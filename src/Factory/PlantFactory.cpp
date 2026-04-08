//
// Created by hankl on 2026/4/8.
//
#include "Factory/PlantFactory.hpp"

#include "Entity/Peashooter.hpp"
#include "Entity/Sunflower.hpp"

// 之後你有實作這些類別時，再把 include 打開
// #include "Entity/CherryBomb.hpp"
// #include "Entity/WallNut.hpp"
// #include "Entity/PotatoMine.hpp"
// #include "Entity/SnowPea.hpp"
// #include "Entity/Chomper.hpp"
// #include "Entity/RepeaterPea.hpp"

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

            // 你之後有實作對應類別時再打開
            /*
            case PlantType::CHERRY_BOMB:
                return std::make_shared<CherryBomb>(row, col, position);

            case PlantType::WALLNUT:
                return std::make_shared<WallNut>(row, col, position);

            case PlantType::POTATO_MINE:
                return std::make_shared<PotatoMine>(row, col, position);

            case PlantType::SNOW_PEA:
                return std::make_shared<SnowPea>(row, col, position);

            case PlantType::CHOMPER:
                return std::make_shared<Chomper>(row, col, position);

            case PlantType::REPEATER_PEA:
                return std::make_shared<RepeaterPea>(row, col, position);
            */

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

        case PlantType::WALLNUT:
            return 50;

        case PlantType::POTATO_MINE:
            return 25;

        case PlantType::SNOW_PEA:
            return 175;

        case PlantType::CHOMPER:
            return 150;

        case PlantType::REPEATER_PEA:
            return 200;

        default:
            return 9999;
    }
}