#ifndef CHERRYBOMB_HPP
#define CHERRYBOMB_HPP

#include "Entity/Plant.hpp"

class CherryBomb : public Plant {
public:
    CherryBomb(int row, int col, const glm::vec2& position);

    void Update() override;

    bool IsExploded() const { return m_Exploded; }
    float GetExplosionRadius() const { return 200.0f; }

protected:
    void InitAnimations() override;

private:
    float m_ExplodeTimer = 0.0f;
    float m_ExplodeDelay = 1.2f;
    bool m_Exploded = false;
};

#endif // CHERRYBOMB_HPP
