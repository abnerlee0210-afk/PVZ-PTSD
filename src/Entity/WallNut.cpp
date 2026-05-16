//
// Created by hankl on 2026/5/16.
//
#include "Entity/WallNut.hpp"
#include "Factory/AnimationFactory.hpp"

WallNut::WallNut(int row, int col, const glm::vec2& position)
    : Plant(
        RESOURCE_DIR "/graphics/Plants/WallNut/WallNut/WallNut_0.png",
        row,
        col,
        position,
        400,   // HP，可再調高
        50     // cost
    ) {
    InitAnimations();
    m_AnimController.SetState(PlantAnimState::COMPLETE);
    SetDrawable(m_AnimController.GetCurrentAnimation());
}

void WallNut::Update() {
    if (!m_Alive) {
        return;
    }
    UpdateAnimationState();

    // WallNut 不攻擊、不產陽光，暫時不用做事
}

void WallNut::InitAnimations() {
    auto complete = AnimationFactory::CreateWallNutComplete();
    auto cracked1 = AnimationFactory::CreateWallNutCracked1();
    auto cracked2 = AnimationFactory::CreateWallNutCracked2();

    m_AnimController.AddAnimation(PlantAnimState::COMPLETE, complete);
    m_AnimController.AddAnimation(PlantAnimState::CRACKED1, cracked1);
    m_AnimController.AddAnimation(PlantAnimState::CRACKED2, cracked2);
}

void WallNut::UpdateAnimationState() {
    if (m_HP >= (MAX_HP*0.6)) {
        m_AnimController.SetState(PlantAnimState::COMPLETE);
    }
    else if (m_HP >= (MAX_HP*0.3)) {
        m_AnimController.SetState(PlantAnimState::CRACKED1);
    }
    else {
        m_AnimController.SetState(PlantAnimState::CRACKED2);
    }

    auto anim = m_AnimController.GetCurrentAnimation();
    if (anim) {
        SetDrawable(anim);
    }
}