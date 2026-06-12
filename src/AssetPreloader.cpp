//
// Created by LAB1223 on 2026/6/12.
//
#include "AssetPreloader.hpp"

#include "Util/Image.hpp"
#include "Factory/AnimationFactory.hpp"

std::vector<std::shared_ptr<Util::Animation>> AssetPreloader::s_Animations;

void AssetPreloader::PreloadAllAnimations() {
    if (!s_Animations.empty()) {
        return;
    }

    s_Animations.push_back(AnimationFactory::CreateSunIdle());
    s_Animations.push_back(AnimationFactory::CreateSunflowerIdle());
    s_Animations.push_back(AnimationFactory::CreatePeashooterIdle());
    s_Animations.push_back(AnimationFactory::CreateSnowPeashooterIdle());
    s_Animations.push_back(AnimationFactory::CreateRepeaterPeaIdle());
    s_Animations.push_back(AnimationFactory::CreateChomperIdle());

    s_Animations.push_back(AnimationFactory::CreateWallNutComplete());
    s_Animations.push_back(AnimationFactory::CreateWallNutCracked1());
    s_Animations.push_back(AnimationFactory::CreateWallNutCracked2());

    s_Animations.push_back(AnimationFactory::CreateCherryBombexplode());
    s_Animations.push_back(AnimationFactory::CreateChomperAttack());
    s_Animations.push_back(AnimationFactory::CreateChomperDigest());

    s_Animations.push_back(AnimationFactory::CreatePotatoMineInit());
    s_Animations.push_back(AnimationFactory::CreatePotatoMineArmed());
    s_Animations.push_back(AnimationFactory::CreatePotatoMineExplode());

    s_Animations.push_back(AnimationFactory::CreateBasicZombieWalk());
    s_Animations.push_back(AnimationFactory::CreateConeheadZombieWalk());
    s_Animations.push_back(AnimationFactory::CreatePoleVaultingZombieWalk());
    s_Animations.push_back(AnimationFactory::CreateBucketheadZombieWalk());

    s_Animations.push_back(AnimationFactory::CreateBasicZombieAttack());
    s_Animations.push_back(AnimationFactory::CreateConeheadZombieAttack());
    s_Animations.push_back(AnimationFactory::CreatePoleVaultingZombieAttack());
    s_Animations.push_back(AnimationFactory::CreateBucketheadZombieAttack());

    s_Animations.push_back(AnimationFactory::CreatePoleVaultingZombieJump());
    s_Animations.push_back(AnimationFactory::CreatePoleVaultingZombieRun());

    s_Animations.push_back(AnimationFactory::CreateZombieDie());
    s_Animations.push_back(AnimationFactory::CreateZombieBoomDie());

    s_Animations.push_back(AnimationFactory::CreateFlagZombieWalk());
    s_Animations.push_back(AnimationFactory::CreateFlagZombieAttack());
}