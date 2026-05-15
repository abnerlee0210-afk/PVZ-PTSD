//
// Created by hankl on 2026/4/17.
//
#include "Factory/ProjectileFactory.hpp"
#include "Entity/PeaIce.hpp"
#include "Entity/Pea.hpp"
// 之後再加 SnowPea projectile


std::shared_ptr<Projectile> ProjectileFactory::CreateProjectile(
    ProjectileType type,
    int row,
    const glm::vec2& position
) {
    switch (type) {
        case ProjectileType::PEA:
            return std::make_shared<Pea>(row, position);

    case ProjectileType::SNOW_PEA:
        // 假設你在工廠函式中可以取得 row 資訊
            return std::make_shared<PeaIce>(row, position);

        default:
            return nullptr;
    }
}