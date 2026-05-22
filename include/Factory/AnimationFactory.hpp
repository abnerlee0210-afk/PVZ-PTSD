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
    static std::shared_ptr<Util::Animation> CreateSunflowerIdle();
    static std::shared_ptr<Util::Animation> CreatePeashooterIdle();
    static std::shared_ptr<Util::Animation> CreateRepeaterPeaIdle();
    static std::shared_ptr<Util::Animation> CreateSnowPeaIdle();
    static std::shared_ptr<Util::Animation> CreateCherryBombExplode();
    static std::shared_ptr<Util::Animation> CreateChomperIdle();
    static std::shared_ptr<Util::Animation> CreateChomperAttack();
    static std::shared_ptr<Util::Animation> CreateChomperDigest();
    static std::shared_ptr<Util::Animation> CreateZombieBoomDie();
};

#endif
