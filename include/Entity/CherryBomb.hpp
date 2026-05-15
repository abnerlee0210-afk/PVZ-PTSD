#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP

#include "Plant.hpp"

class CherryBomb : public Plant {
public:
    CherryBomb(int row, int col, const glm::vec2& position);
    void Update() override;
    bool IsExploded() const { return m_Exploded; }
    float GetExplosionRadius() const { return 160.0f; } // 160 像素通常能穩定覆蓋 3x3

protected:
    void InitAnimations() override;

private:
    float m_ExplodeTimer = 0.0f;
    float m_ExplodeDelay = 0.6f;
    bool m_Exploded = false;
};

#endif