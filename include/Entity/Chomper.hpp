#ifndef CHOMPER_HPP
#define CHOMPER_HPP

#include <memory>
#include <vector>

#include "Entity/Plant.hpp"
#include "Entity/Zombie.hpp"

enum class ChomperState {
    IDLE,
    ATTACKING,
    CHEWING
};

class Chomper : public Plant {
public:
    Chomper(int row, int col, const glm::vec2& position);

    void Update() override;
    void UpdateWithZombies(const std::vector<std::shared_ptr<Zombie>>& zombies) override;

    ChomperState GetChomperState() const { return m_State; }
    bool IsChewing() const { return m_State == ChomperState::CHEWING; }

protected:
    void InitAnimations() override;

private:
    std::shared_ptr<Zombie> FindTarget(
        const std::vector<std::shared_ptr<Zombie>>& zombies
    ) const;
    void EnterIdle();
    void EnterAttacking(const std::shared_ptr<Zombie>& target);
    void EnterChewing();
    void UpdateAnimationForState();

    ChomperState m_State = ChomperState::IDLE;
    float m_AttackTimer = 0.0f;
    float m_AttackDuration = 0.45f;
    float m_ChewTimer = 0.0f;
    float m_ChewDuration = 30.0f;
    float m_DetectRange = 80.0f;
};

#endif // CHOMPER_HPP
