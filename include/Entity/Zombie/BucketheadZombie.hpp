//
// Created by hankl on 2026/5/31.
//

#ifndef BUCKETHEADZOMBIE_HPP
#define BUCKETHEADZOMBIE_HPP

#include "Entity/Zombie/Zombie.hpp"

class BucketheadZombie : public Zombie {
public:
    BucketheadZombie(int row, const glm::vec2& position);

    void Update() override;

protected:
    void InitAnimations() override;
};

#endif