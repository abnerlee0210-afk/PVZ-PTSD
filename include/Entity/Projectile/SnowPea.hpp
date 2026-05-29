//
// Created by LAB1223 on 2026/5/29.
//

#ifndef SNOWPEAPROJECTILE_HPP
#define SNOWPEAPROJECTILE_HPP

#include "Entity/Projectile/Projectile.hpp"

class SnowPeaProjectile : public Projectile {
public:
    SnowPeaProjectile(int row, const glm::vec2& position);

    bool CanSlow() const override;
};

#endif