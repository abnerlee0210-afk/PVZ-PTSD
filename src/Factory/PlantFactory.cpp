#include "Factory/PlantFactory.hpp"

#include "Entity/CherryBomb.hpp"
#include "Entity/Chomper.hpp"
#include "Entity/Peashooter.hpp"
#include "Entity/RepeaterPea.hpp"
#include "Entity/SnowPea.hpp"
#include "Entity/Sunflower.hpp"

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
        case PlantType::SNOW_PEA:
            return std::make_shared<SnowPea>(row, col, position);
        case PlantType::CHOMPER:
            return std::make_shared<Chomper>(row, col, position);
        case PlantType::REPEATER_PEA:
            return std::make_shared<RepeaterPea>(row, col, position);
        case PlantType::WALLNUT:
        case PlantType::POTATO_MINE:
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
