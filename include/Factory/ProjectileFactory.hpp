//
// Created by hankl on 2026/4/17.
//

#ifndef PROJECTILE_FACTORY_HPP
#define PROJECTILE_FACTORY_HPP

#include "pch.hpp"

#include "Entity/Projectile.hpp"
#include "Level/LevelTypes.hpp"

class ProjectileFactory {
public:
    static std::shared_ptr<Projectile> CreateProjectile(
        ProjectileType type,
        int row,
        const glm::vec2& position
    );
};

#endif // PROJECTILE_FACTORY_HPP