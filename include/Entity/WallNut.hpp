//
// Created by hankl on 2026/5/16.
//

#ifndef WALLNUT_HPP
#define WALLNUT_HPP

#include "Entity/Plant.hpp"

enum class WallNutState {
    COMPLETE,
    CRACKED1,
    CRACKED2
};

class WallNut : public Plant {
public:
    WallNut(int row, int col, const glm::vec2& position);

    void Update() override;

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;
private:
    int MAX_HP = 400;
};

#endif
