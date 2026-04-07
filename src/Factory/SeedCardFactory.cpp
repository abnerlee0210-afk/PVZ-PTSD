//
// Created by hankl on 2026/4/7.
//
#include "Factory/SeedCardFactory.hpp"

std::shared_ptr<SeedCard> SeedCardFactory::CreateSeedCard(PlantType type, const glm::vec2& position) {
    switch (type) {
    case PlantType::PEASHOOTER:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_peashooter.png",
            PlantType::PEASHOOTER,
            100,
            5.0f,
            position
        );

    case PlantType::SUNFLOWER:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_sunflower.png",
            PlantType::SUNFLOWER,
            50,
            5.0f,
            position
        );

    case PlantType::CHERRY_BOMB:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_cherrybomb.png",
            PlantType::CHERRY_BOMB,
            150,
            8.0f,
            position
        );

    case PlantType::WALLNUT:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_wallnut.png",
            PlantType::WALLNUT,
            50,
            10.0f,
            position
        );

    case PlantType::POTATO_MINE:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_potatomine.png",
            PlantType::POTATO_MINE,
            25,
            8.0f,
            position
        );

    case PlantType::SNOW_PEA:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_snowpea.png",
            PlantType::SNOW_PEA,
            175,
            7.0f,
            position
        );

    case PlantType::CHOMPER:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_chomper.png",
            PlantType::CHOMPER,
            150,
            7.0f,
            position
        );

    case PlantType::REPEATER_PEA:
        return std::make_shared<SeedCard>(
            RESOURCE_DIR "/graphics/Cards/card_repeaterpea.png",
            PlantType::REPEATER_PEA,
            200,
            7.0f,
            position
        );

    default:
        return nullptr;
    }
}