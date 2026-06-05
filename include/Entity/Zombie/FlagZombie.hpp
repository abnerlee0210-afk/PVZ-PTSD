//
// Created by hankl on 2026/6/5.
//

#ifndef FLAGZOMBIE_HPP
#define FLAGZOMBIE_HPP

#include "Entity/Zombie//Zombie.hpp"

class FlagZombie : public Zombie {
public:
    FlagZombie(int row, const glm::vec2& position);

    void Update() override;

protected:
    void InitAnimations() override;
};

#endif
