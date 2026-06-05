//
// Created by hankl on 2026/4/8.
//
#include "Factory/ZombieFactory.hpp"
#include "Entity/Zombie/BasicZombie.hpp"
#include "Entity/Zombie/ConeheadZombie.hpp"
#include "Entity/Zombie/PoleVaultingZombie.hpp"
#include "Entity/Zombie/BucketheadZombie.hpp"
#include "Entity/Zombie/FlagZombie.hpp"

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
        case ZombieType::POLE_VAULTING:
            return std::make_shared<PoleVaultingZombie>(row,position);
        case ZombieType::BUCKETHEAD:
            return std::make_shared<BucketheadZombie>(row, position);
        case ZombieType::FLAG:
            return std::make_shared<FlagZombie>(row, position);
        default:
            return nullptr;
    }

}