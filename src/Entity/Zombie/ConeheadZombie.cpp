//
// Created by hankl on 2026/3/20.
//
#include "Entity/Zombie/ConeheadZombie.hpp"
#include "Factory/AnimationFactory.hpp"

ConeheadZombie::ConeheadZombie(int row, const glm::vec2& position)
    : Zombie(RESOURCE_DIR "/graphics/Zombies/ConeheadZombie/coneheadZombie/ConeheadZombie_0.png",
        row,
        position,
        20,
        1,
        10.0f) {
    InitAnimations();
    m_AnimController.SetState(ZombieAnimState::WALK);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void ConeheadZombie::Update() {
    Zombie::Update();
}

void ConeheadZombie::InitAnimations() {
    auto walk = AnimationFactory::CreateConeheadZombieWalk();
    auto attack = AnimationFactory::CreateConeheadZombieAttack();
    auto die = AnimationFactory::CreateZombieDie();
    auto boomDieAnim = AnimationFactory::CreateZombieBoomDie();


    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, die);
    m_AnimController.AddAnimation(ZombieAnimState::BOOM_DIE, boomDieAnim);

}