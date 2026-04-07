//
// Created by hankl on 2026/4/7.
//

#ifndef SEEDCARDFACTORY_HPP
#define SEEDCARDFACTORY_HPP



#include "pch.hpp"

#include "Level/LevelTypes.hpp"
#include "UI/SeedCard.hpp"

class SeedCardFactory {
public:
    static std::shared_ptr<SeedCard> CreateSeedCard(PlantType type, const glm::vec2& position);
};

#endif //SEEDCARDFACTORY_HPP
