//
// Created by hankl on 2026/5/31.
//

#ifndef REPEATER_HPP
#define REPEATER_HPP

#include "Entity/Plant//Plant.hpp"

class RepeaterPea : public Plant {
public:
    RepeaterPea(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanShoot() const override;
    glm::vec2 GetProjectileSpawnPosition() const override;
    void ResetShootTimer() override;
    ProjectileType GetProjectileType() const override;

    std::vector<float> GetProjectileFireDelays() const override;

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;

private:
    float m_ShootTimer = 0.0f;
    float m_ShootInterval = 1.5f;
};

#endif
