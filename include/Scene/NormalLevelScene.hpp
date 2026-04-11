//
// Created by 李政翰 on 2026/4/7.
//

#ifndef NORMALLEVELSCENE_HPP
#define NORMALLEVELSCENE_HPP

#include "Scene/Scene.hpp"
#include "Screen/BackgroundImage.hpp"
#include "Level/LevelConfig.hpp"
#include "Board/GameBoard.hpp"

#include "UI/SeedCard.hpp"
#include "UI/SeedChooser.hpp"
#include "UI/Base/Button.hpp"

#include "Factory/SeedCardFactory.hpp"

#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include <random>

#include "Entity/Plant.hpp"
#include "Entity/Zombie.hpp"
#include "Entity/Projectile.hpp"
#include "Entity/Sun.hpp"

class SceneManager;

enum class GameState {
    PLAYING,
    VICTORY,
    GAME_OVER
};

class NormalLevelScene : public Scene {
public:
    explicit NormalLevelScene(const LevelConfig& config, SceneManager* manager);

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

private:
    // ============================
    // Init
    // ============================
    void CreateBackground();
    void CreateSeedChooserFromConfig();
    void CreateButton();
    void UpdateSunText();

    // ============================
    // Input
    // ============================
    void HandleInput();  // 只管輸入邊界
    void ProcessMouseClick(); // 管流程
    bool TrySelectSeedCard(const glm::vec2& mousePos); // 管UI選卡
    bool TryCollectSun(const glm::vec2& mousePos);
    bool CanPlantAt(int row,int col, PlantType type) const; // 驗證是否可種植
    void PlacePlantAt(int row,int col, PlantType type); // 執行種植


    // ============================
    // Wave / Spawning
    // ============================
    void UpdateWaveSpawning();
    void SpawnZombieByType(ZombieType type, int row);
    void SpawnZombiesFromEvent(const SpawnEvent& event);
    void SpawnProjectile(const std::shared_ptr<Projectile>& projectile);
    void SpawnSkySun();
    void SpawnSun(const std::shared_ptr<Sun>& sun);

    // ============================
    // Update
    // ============================
    void UpdateSkySunSystem(float deltaTime);
    void UpdateProjectiles();
    void UpdateZombies();
    void UpdatePlants();
    void UpdateSuns();
    void UpdateSinglePlant(const std::shared_ptr<Plant>& plant);
    void TryHandlePlantShooting(const std::shared_ptr<Plant>& plant);


    // ============================
    // 處理碰撞 / 偵測殭屍是否出現與植物同列
    // ============================
    void CheckProjectileZombieCollisions();
    void CheckZombiePlantCollisions();
    bool IsZombieInRow(const std::shared_ptr<Plant>& plant) const;

    // ============================
    // Win / Lose
    // ============================
    bool AreAllWavesFinished() const;
    bool AreAllZombiesCleared() const;
    void CheckVictory();
    void CheckGameOver();
    void EnterVictory();
    void EnterGameOver();

    // ============================
    // Cleanup
    // ============================
    void RemoveDeadEntities();
    void RemoveAllEntity();




private:
    // ============================
    // 基本資料
    // ============================
    SceneManager* m_Manager;
    LevelConfig m_Config;

    // ============================
    // 地圖/UI
    // ============================
    GameBoard m_Board;
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<SeedChooser> m_SeedChooser;

    // ============================
    // 遊戲狀態
    // ============================
    int m_SunPoints = 0;
    float m_LevelTimer = 0.0f;
    GameState m_GameState = GameState::PLAYING;

    // 這邊應該要移出NormalLevelScene，放進Sun中嗎？
    float m_SkySunTimer = 0.0f;
    float m_NextSkySunInterval = 5.0f;

    // ============================
    // Entities
    // ============================
    std::vector<std::shared_ptr<Zombie>> m_Zombies;
    std::vector<std::shared_ptr<Plant>> m_Plants;
    std::vector<std::shared_ptr<Projectile>> m_Projectiles;
    std::vector<std::shared_ptr<Sun>> m_Suns;

    // ============================
    // Input狀態
    // ============================
    bool m_WasMousePressed = false;
    

    //
    std::mt19937 m_Rng{std::random_device{}()};
    glm::vec2 m_CameraOffect = {0.0f,0.0f};

};

#endif //NORMALLEVELSCENE_HPP
