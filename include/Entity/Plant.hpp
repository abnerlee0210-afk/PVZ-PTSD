//
// Created by hankl on 2026/3/10.
//

#ifndef PLANT_HPP
#define PLANT_HPP

#include "pch.hpp"


#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

#include "Level/LevelTypes.hpp"
#include "Animation/AnimationStateController.hpp"

enum class PlantAnimState {
    IDLE,
    ATTACK,
    DIE
};

class Plant : public Util::GameObject {
public:
    Plant(const std::string& imagePath,
          int row,
          int col,
          const glm::vec2& position,
          int hp,
          int cost);
    virtual ~Plant() = default;

    virtual void Update() {}
    virtual void TakeDamage(int damage);

    int GetRow() const { return m_Row; }
    int GetCol() const { return m_Col; }
    int GetHP() const { return m_HP; }
    int GetCost() const { return m_Cost; }
    bool IsAlive() const { return m_Alive; }

    virtual bool CanShoot() const { return false; }
    virtual ProjectileType GetProjectileType() const { return  ProjectileType::PEA;}
    virtual glm::vec2 GetProjectileSpawnPosition() const { return {0.0f, 0.0f}; }
    virtual void ResetShootTimer() {}

    virtual bool CanGenerateSun() const { return false; }
    virtual glm::vec2 GetSunSpawnPosition() const { return {0.0f, 0.0f}; }
    virtual void ResetSunTimer() {}

    virtual void InitAnimations(){}
    void UpdateAnimationState();

protected:
    int m_Row;
    int m_Col;
    int m_HP;
    int m_Cost;
    bool m_Alive;

    AnimationStateController<PlantAnimState> m_AnimController;
};

#endif //PLANT_HPP