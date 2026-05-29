//
// Created by LAB1223 on 2026/5/29.
//

#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_SNOWPEASHOOTER_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_SNOWPEASHOOTER_HPP

#include "Entity/Plant/Plant.hpp"

class SnowPeashooter : public Plant {
public:
    SnowPeashooter(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanShoot() const override;
    glm::vec2 GetProjectileSpawnPosition() const override;
    void ResetShootTimer() override;
    ProjectileType GetProjectileType() const override;

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;

private:
    float m_ShootTimer = 0.0f;
    float m_ShootInterval = 2.1f;
};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_SNOWPEASHOOTER_HPP
