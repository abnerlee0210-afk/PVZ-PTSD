//
// Created by 李政翰 on 2026/3/31.
//

#ifndef MENUSCENE_HPP
#define MENUSCENE_HPP

#include "pch.hpp"
#include <memory>

#include "Scene.hpp"
#include "Screen/BackgroundImage.hpp"
#include "UI/Base/Button.hpp"
#include "Util/Renderer.hpp"
#include "Util/Logger.hpp"

#include "Util/Input.hpp"
#include "functional"
#include <iostream>

class SceneManager; // 前向宣告，避免循環包含

class MenuScene : public Scene
{
public:
    // 修改建構子，接收 SceneManager 的指標
    explicit MenuScene(SceneManager* manager);
    ~MenuScene();

    void on_enter() override;
    void on_update() override;
    void on_render() override;
    void on_exit() override;

private:
    SceneManager* m_Manager; // 用原始指標即可，因為 Manager 的生命週期比 Scene 長

    // MenuScene 物件
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Button> m_PlayButton;

    // 圖片資源Path
    std::string BackgroundImagePath = RESOURCE_DIR "/graphics/Screen/MainMenu.png";
    std::string PlayButtonNormal = RESOURCE_DIR "/graphics/Screen/Adventure_0.png";
    std::string PlayButtonFeedback = RESOURCE_DIR "/graphics/Screen/Adventure_1.png";
};

#endif //MENUSCENE_HPP
