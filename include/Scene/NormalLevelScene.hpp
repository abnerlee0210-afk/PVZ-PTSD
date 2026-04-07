//
// Created by 李政翰 on 2026/4/7.
//

#ifndef NORMALLEVELSCENE_HPP
#define NORMALLEVELSCENE_HPP

#include "Scene/Scene.hpp"

#include "Level/LevelConfig.hpp"
#include "Board/GameBoard.hpp"
#include "UI/SeedCard.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"

class NormalLevelScene : public Scene {
public:
    explicit NormalLevelScene(const LevelConfig& config);

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
    LevelConfig m_Config;
    GameBoard m_Board;

    std::shared_ptr<Util::GameObject> m_Background;
    std::shared_ptr<Util::Text> m_SunText;
    std::shared_ptr<Util::GameObject> m_SunTextObject;

    std::vector<std::shared_ptr<SeedCard>> m_SeedCards;

    int m_SunPoints = 0;
};

#endif //NORMALLEVELSCENE_HPP
