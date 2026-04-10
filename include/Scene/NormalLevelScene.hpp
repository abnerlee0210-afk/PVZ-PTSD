//
// Created by 李政翰 on 2026/4/7.
//

#ifndef NORMALLEVELSCENE_HPP
#define NORMALLEVELSCENE_HPP

#include "Scene/Scene.hpp"
#include "Screen/BackgroundImage.hpp"
#include "Screen/Text.hpp"
#include "Level/LevelConfig.hpp"
#include "Board/GameBoard.hpp"

#include "UI/SeedCard.hpp"
#include "UI/SeedChooser.hpp"

#include "Factory/SeedCardFactory.hpp"

#include "Util/Image.hpp"
#include "Util/Text.hpp"

#include "Entity/Plant.hpp"
#include "Entity/Peashooter.hpp"
#include "Entity/Zombie.hpp"
#include "Entity/BasicZombie.hpp"
#include "Entity/Projectile.hpp"
#include "Entity/Pea.hpp"

class SceneManager;

class NormalLevelScene : public Scene {
public:
    explicit NormalLevelScene(const LevelConfig& config, SceneManager* manager);

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

private:
    // ============================
    // 初始化
    // ============================
    void CreateBackground();
    void CreateSeedChooserFromConfig();
    void UpdateSunText();

    // ============================
    // Input
    // ============================
    void HandleInput();  // 只管輸入邊界
    void ProcessMouseClick(); // 管流程

    bool TrySelectSeedCard(const glm::vec2& mousePos); // 管UI選卡
    bool CanPlantAt(int row,int col, PlantType type) const; // 驗證是否可種植
    void PlacePlantAt(int row,int col, PlantType type); // 執行種植

    // ============================
    // Wave / Spawning (Zombie)
    // ============================
    void UpdateWaveSpawning();
    void SpawnZombieByType(ZombieType type, int row);
    void SpawnZombiesFromEvent(const SpawnEvent& event);
    void SpawnProjectile(const std::shared_ptr<Projectile>& projectile);

    // ============================
    // 更新
    // ============================
    void UpdateProjectiles();
    void UpdateZombies();
    void UpdatePlants();
    void UpdateSinglePlant(const std::shared_ptr<Plant>& plant);
    void TryHandlePlantShooting(const std::shared_ptr<Plant>& plant);


    // ============================
    // 處理碰撞 / 偵測殭屍是否出現與植物同列
    // ============================
    void CheckProjectileZombieCollisions();
    void CheckZombiePlantCollisions();
    bool IsZombieInRow(const std::shared_ptr<Plant>& plant) const;

    // ============================
    // 清理(死亡物件)
    // ============================
    void RemoveDeadProjectiles();
    void RemoveDeadZombies();
    void RemoveDeadPlants();




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

    // ============================
    // Entities
    // ============================
    std::vector<std::shared_ptr<Zombie>> m_Zombies;
    std::vector<std::shared_ptr<Plant>> m_Plants;
    std::vector<std::shared_ptr<Projectile>> m_Projectiles;

    // ============================
    // Input狀態
    // ============================
    bool m_WasMousePressed = false;
    
    // ============================
    // Pos / Dir
    // ============================
    glm::vec2 SeedChooserPos = glm::vec2(-300.0f, 260.0f);
    std::string fontDir = RESOURCE_DIR "/font.ttf";

};

#endif //NORMALLEVELSCENE_HPP
