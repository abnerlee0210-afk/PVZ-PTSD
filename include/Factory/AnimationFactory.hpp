//
// Created by hankl on 2026/4/24.
//

#ifndef ANIMATION_FACTORY_HPP
#define ANIMATION_FACTORY_HPP

#include "pch.hpp"

#include <memory>

#include "Util/Animation.hpp"

class AnimationFactory {
public:
    static std::shared_ptr<Util::Animation> CreateBasicZombieWalk();
    static std::shared_ptr<Util::Animation> CreateConeheadZombieWalk();

    static std::shared_ptr<Util::Animation> CreateSunIdle();
    static std::shared_ptr<Util::Animation> CreateSunflowerIdle();
    static std::shared_ptr<Util::Animation> CreatePeashooterIdle();
    static std::shared_ptr<Util::Animation> CreateWallNutComplete();
    static std::shared_ptr<Util::Animation> CreateWallNutCracked1();
    static std::shared_ptr<Util::Animation> CreateWallNutCracked2();

    static std::shared_ptr<Util::Animation> CreateBasicZombieAttack();
    static std::shared_ptr<Util::Animation> CreateConeheadZombieAttack();
};

#endif
