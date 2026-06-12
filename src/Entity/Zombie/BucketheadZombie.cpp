//
// Created by hankl on 2026/5/31.
//
#include "Entity/Zombie/BucketheadZombie.hpp"

#include "Factory/AnimationFactory.hpp"

BucketheadZombie::BucketheadZombie(int row, const glm::vec2& position)
    : Zombie(
        RESOURCE_DIR "/graphics/Zombies/BucketheadZombie/BucketheadZombie/BucketheadZombie_0.png",
        row,
        position,
        50,
        1,
        10.0f
    ) {
    InitAnimations();
    m_AnimController.SetState(ZombieAnimState::WALK);
    SetDrawable(m_AnimController.GetCurrentAnimation());

    m_CollisionRadius = 32.0f;
    m_AttackRange = 22.0f;
}

void BucketheadZombie::Update() {
    Zombie::Update();
}

void BucketheadZombie::InitAnimations() {
    auto walk = AnimationFactory::CreateBucketheadZombieWalk();
    auto attack = AnimationFactory::CreateBucketheadZombieAttack();
    auto die = AnimationFactory::CreateZombieDie();
    auto boomDieAnim = AnimationFactory::CreateZombieBoomDie();

    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, die);
    m_AnimController.AddAnimation(ZombieAnimState::BOOM_DIE, boomDieAnim);
}