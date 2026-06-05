//
// Created by hankl on 2026/6/5.
//
#include "Entity/Zombie/FlagZombie.hpp"

#include "Factory/AnimationFactory.hpp"

FlagZombie::FlagZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/FlagZombie/FlagZombie/FlagZombie_0.png",
        row,
        position,
        12,
        20,
        18.0f
    ) {
    InitAnimations();
    m_AnimController.SetState(ZombieAnimState::WALK);
    SetDrawable(m_AnimController.GetCurrentAnimation());

    m_CollisionRadius = 30.0f;
    m_AttackRange = 22.0f;
}

void FlagZombie::Update() {
    Zombie::Update();
}

void FlagZombie::InitAnimations() {
    auto walk = AnimationFactory::CreateFlagZombieWalk();
    auto attack = AnimationFactory::CreateFlagZombieAttack();
    auto die = AnimationFactory::CreateZombieDie();
    auto boomDie = AnimationFactory::CreateZombieBoomDie();

    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, die);
    m_AnimController.AddAnimation(ZombieAnimState::BOOM_DIE, boomDie);
}