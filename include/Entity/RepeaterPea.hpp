#ifndef REPEATERPEA_HPP
#define REPEATERPEA_HPP

#include "Entity/Plant.hpp"

class RepeaterPea : public Plant {
public:
    RepeaterPea(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanShoot() const override;
    ProjectileType GetProjectileType() const override;
    glm::vec2 GetProjectileSpawnPosition() const override;
    int GetProjectileCountPerShot() const override;
    glm::vec2 GetProjectileSpawnPositionByIndex(int projectileIndex) const override;
    void ResetShootTimer() override;

protected:
    void InitAnimations() override;

private:
    float m_ShootInterval;
    float m_ShootTimer;
};

#endif // REPEATERPEA_HPP
