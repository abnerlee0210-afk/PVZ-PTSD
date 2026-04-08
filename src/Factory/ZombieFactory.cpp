//
// Created by hankl on 2026/4/8.
//
#include "Factory/ZombieFactory.hpp"
#include "Entity/BasicZombie.hpp"
#include "Entity/ConeheadZombie.hpp"

std::shared_ptr<Zombie> ZombieFactory::CreateZombie(
    ZombieType type,
    int row,
    const glm::vec2& position
) {
    switch (type) {
        case ZombieType::BASIC:
            return std::make_shared<BasicZombie>(row,position);
        case ZombieType::CONEHEAD:
            return std::make_shared<ConeheadZombie>(row,position);
        default:
            return nullptr;
    }

}