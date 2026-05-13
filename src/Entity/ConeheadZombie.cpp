//
// Created by hankl on 2026/3/20.
//
#include "Entity/ConeheadZombie.hpp"
#include "Factory/AnimationFactory.hpp"

ConeheadZombie::ConeheadZombie(int row, const glm::vec2& position)
    : Zombie(RESOURCE_DIR "/graphics/Zombies/ConeheadZombie/coneheadZombie/ConeheadZombie_0.png", row, position, 20, 18.0f) {
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

    m_AnimController.AddAnimation(ZombieAnimState::WALK, walk);
    m_AnimController.AddAnimation(ZombieAnimState::ATTACK, attack);
    m_AnimController.AddAnimation(ZombieAnimState::DIE, walk);
}