//
// Created by hankl on 2026/5/31.
//

#ifndef CHOMPER_HPP
#define CHOMPER_HPP

#include "Entity/Plant/Plant.hpp"

class Chomper : public Plant {
public:
    Chomper(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanBite() const override;
    bool IsDigesting() const override;
    float GetBiteRange() const override;
    void BiteZombie() override;

protected:
    void InitAnimations() override;
    void UpdateAnimationState() override;

private:
    bool m_IsDigesting = false;
    float m_DigestTimer = 0.0f;
    float m_DigestDuration = 25.0f;
    float m_BiteRange = 50.0f;
};

#endif
