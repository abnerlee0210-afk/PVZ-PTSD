#ifndef SNOWPEA_HPP
#define SNOWPEA_HPP

#include "Plant.hpp"

class SnowPea : public Plant {
public:
    SnowPea(int row, int col, const glm::vec2& position);

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

#endif //SNOWPEA_HPP