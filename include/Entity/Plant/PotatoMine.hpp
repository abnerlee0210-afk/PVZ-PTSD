#ifndef POTATOMINE_HPP
#define POTATOMINE_HPP

#include "Plant.hpp"

class PotatoMine : public Plant {
public:
    PotatoMine(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanExplodeOnContact() const override;
    int GetContactExplosionDamage() const override;
    void TriggerContactExplosion() override;

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;

private:
    bool m_IsArmed = false;
    bool m_IsExploding = false;
    bool m_HasExploded = false;

    float m_ArmTimer = 0.0f;
    float m_ArmDelay = 12.0f;

    float m_ExplodeTimer = 0.0f;
    float m_ExplodeDuration = 0.6f;

    float m_ArmedGraceTimer = 0.0f;
    float m_ArmedGraceDuration = 0.25f;
};

#endif