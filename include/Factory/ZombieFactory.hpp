//
// Created by hankl on 2026/4/8.
//

#ifndef ZOMBIEFACTORY_HPP
#define ZOMBIEFACTORY_HPP

#include "pch.hpp"

#include "Level/LevelTypes.hpp"
#include "Entity/Zombie.hpp"

class ZombieFactory {
public:
    static std::shared_ptr<Zombie> CreateZombie(
        ZombieType type,
        int row,
        const glm::vec2& position);
};


#endif //ZOMBIEFACTORY_HPP
