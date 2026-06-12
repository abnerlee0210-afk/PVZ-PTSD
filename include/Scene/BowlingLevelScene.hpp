//
// Created by 李政翰 on 2026/4/7.
//

#ifndef BOWLINGLEVELSCENE_HPP
#define BOWLINGLEVELSCENE_HPP

#include "Scene/Scene.hpp"
#include "Level/LevelConfig.hpp"
#include "Board/GameBoard.hpp"
#include "Screen/BackgroundImage.hpp"

#include "Entity/Plant/Plant.hpp"
#include "Entity/Zombie/Zombie.hpp"

class SceneManager;

class BowlingLevelScene : public Scene {
public:
    BowlingLevelScene(const LevelConfig& config, SceneManager* manager);

    void SetLevelConfig(const LevelConfig& config);

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

private:
    void CreateBackground();
    void HandleInput();
    void UpdateZombies();
    void UpdateBowlingNuts();
    void UpdateWaveSpawning();

    void SpawnZombieByType(ZombieType type, int row);
    void SpawnZombiesFromEvent(const SpawnEvent& event);

private:
    SceneManager* m_Manager = nullptr;
    LevelConfig m_Config;

    GameBoard m_Board;

    std::shared_ptr<BackgroundImage> m_Background;

    float m_LevelTimer = 0.0f;
    bool m_WasMousePressed = false;

    std::vector<std::shared_ptr<Zombie>> m_Zombies;
};

#endif
