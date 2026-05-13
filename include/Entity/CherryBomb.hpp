//
// Created by hankl on 2026/5/12.
//

#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP

#include "Entity/Plant.hpp"

class CherryBomb : public Plant {
public:
    CherryBomb(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanExplode() const override;
    glm::vec2 GetExplosionCenter() const override;
    float GetExplosionRadius() const override;
    int GetExplosionDamage() const override;
    void MarkExploded() override;

private:
    float m_ExplodeTimer = 0.0f;
    float m_ExplodeDelay = 1.0f;
    bool m_HasExploded = false;
};

#endif // CHERRYBOMB_HPP
