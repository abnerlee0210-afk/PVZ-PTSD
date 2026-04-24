//
// Created by hankl on 2026/3/10.
//
#include "Entity/BasicZombie.hpp"
#include "Factory/AnimationFactory.hpp"

#include "Util/Logger.hpp"

BasicZombie::BasicZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/NormalZombie/Zombie/Zombie_0.png",
        row,
        position,
        12,
        18.0f) {
    InitAnimations();
    m_AnimController.SetState(ZombieAnimState::WALK);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void BasicZombie::Update() {
    Zombie::Update();
}

void BasicZombie::InitAnimations() {
    auto walk = AnimationFactory::CreateBasicZombieWalk();

    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, walk);
}
