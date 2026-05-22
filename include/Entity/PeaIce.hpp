#ifndef PEAICE_HPP
#define PEAICE_HPP

#include "Entity/Projectile.hpp"

class PeaIce : public Projectile {
public:
    PeaIce(int row, const glm::vec2& position);

    void Update() override;
    bool AppliesSlowEffect() const override;
};

#endif // PEAICE_HPP
