//
// Created by hankl on 2026/4/17.
//
#include "Factory/ProjectileFactory.hpp"

#include "Entity/Pea.hpp"
// 之後再加 SnowPea projectile
// #include "Entity/SnowPeaProjectile.hpp"

std::shared_ptr<Projectile> ProjectileFactory::CreateProjectile(
    ProjectileType type,
    int row,
    const glm::vec2& position
) {
    switch (type) {
        case ProjectileType::PEA:
            return std::make_shared<Pea>(row, position);

        case ProjectileType::SNOW_PEA:
            // 之後補
                return nullptr;

        default:
            return nullptr;
    }
}