//
// Created by hankl on 2026/4/17.
//
#include "Factory/ProjectileFactory.hpp"

#include "Entity/Projectile/Pea.hpp"
#include "Entity/Projectile/SnowPea.hpp"

std::shared_ptr<Projectile> ProjectileFactory::CreateProjectile(
    ProjectileType type,
    int row,
    const glm::vec2& position
) {
    switch (type) {
        case ProjectileType::PEA:
            return std::make_shared<Pea>(row, position);

        case ProjectileType::SNOW_PEA:
            return std::make_shared<SnowPeaProjectile>(row, position);;

        default:
            return nullptr;
    }
}