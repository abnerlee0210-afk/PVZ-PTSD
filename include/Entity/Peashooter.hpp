//
// Created by hankl on 2026/3/10.
//

#ifndef PEASHOOTER_HPP
#define PEASHOOTER_HPP

#include "Plant.hpp"

class Peashooter : public Plant {
public:
    Peashooter(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanShoot() const override;
    ProjectileType GetProjectileType() const override;
    glm::vec2 GetProjectileSpawnPosition() const override;
    void ResetShootTimer() override;

protected:
    void InitAnimations() override;

private:
    float m_ShootInterval;
    float m_ShootTimer;
};

#endif //PEASHOOTER_HPP