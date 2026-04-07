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

#include "Factory/SeedCardFactory.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"

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
    void CreateSunText();
    void CreateSeedCardsFromConfig();
    void UpdateSunText();

private:
    SceneManager* m_Manager;

    LevelConfig m_Config;
    GameBoard m_Board;

    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Text> m_SunText;

    std::vector<std::shared_ptr<SeedCard>> m_SeedCards;

    int m_SunPoints = 0;


    std::string fontDir = RESOURCE_DIR "/font.ttf";
};

#endif //NORMALLEVELSCENE_HPP
