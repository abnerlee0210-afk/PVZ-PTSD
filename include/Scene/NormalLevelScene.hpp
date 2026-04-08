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
    void CreateSeedChooserFromConfig();
    void UpdateSunText();

private:
    SceneManager* m_Manager;

    LevelConfig m_Config;
    GameBoard m_Board;

    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Text> m_SunText;

    std::shared_ptr<SeedChooser> m_SeedChooser;

    int m_SunPoints = 0;


    std::string fontDir = RESOURCE_DIR "/font.ttf";
    glm::vec2 SeedChooserPos = glm::vec2(-300.0f, 260.0f);
};

#endif //NORMALLEVELSCENE_HPP
