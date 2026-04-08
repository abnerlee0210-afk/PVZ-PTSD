//
// Created by hankl on 2026/4/8.
//

#ifndef PLANTFACTORY_HPP
#define PLANTFACTORY_HPP

#include "pch.hpp"

#include "Level/LevelTypes.hpp"
#include "Entity/Plant.hpp"

class PlantFactory {
public:
    static std::shared_ptr<Plant> CreatePlant(
        PlantType type,
        int row,
        int col,
        const glm::vec2& position
    );

    static int GetCost(PlantType type);
};

#endif //PLANTFACTORY_HPP
