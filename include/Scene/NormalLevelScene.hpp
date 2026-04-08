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

class SceneManager;

class NormalLevelScene : public Scene {
public:
    explicit NormalLevelScene(const LevelConfig& config, SceneManager* manager);

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

private:
    void CreateBackground();
    void CreateSeedChooserFromConfig();
    void UpdateSunText();

    void HandleInput();  // 只管輸入邊界
    void ProcessMouseClick(); // 管流程
    bool TrySelectSeedCard(const glm::vec2& mousePos); // 管UI選卡
    bool CanPlantAt(int row,int col, PlantType type) const; // 驗證是否可種植
    void PlacePlantAt(int row,int col, PlantType type); // 執行種植

    void SpawnTestZombie();


private:
    SceneManager* m_Manager;

    LevelConfig m_Config;
    GameBoard m_Board;

    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Text> m_SunText;
    std::shared_ptr<SeedChooser> m_SeedChooser;

    int m_SunPoints = 0;
    glm::vec2 SeedChooserPos = glm::vec2(-300.0f, 260.0f);

    std::vector<std::shared_ptr<Plant>> m_Plants;
    bool m_WasMousePressed = false;

    //
    std::vector<std::shared_ptr<Zombie>> m_Zombies;
    //

    std::string fontDir = RESOURCE_DIR "/font.ttf";

};

#endif //NORMALLEVELSCENE_HPP
