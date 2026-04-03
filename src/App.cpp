#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    // 1. 建立場景實體
    auto menu = std::make_shared<MenuScene>(&m_SceneManager);
    auto select = std::make_shared<LevelSelectScene>(&m_SceneManager);

    // 2. 將場景註冊到 Manager (對應你在 SceneManager.hpp 定義的 Enum)
    m_SceneManager.AddScene(SceneManager::SceneType::MENU, menu);
    m_SceneManager.AddScene(SceneManager::SceneType::SELECT, select);

    // 3. 切換到初始場景 (這會自動觸發 MenuScene 的 on_enter)
    m_SceneManager.switch_to(SceneManager::SceneType::MENU);

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    m_SceneManager.on_update();
    m_SceneManager.on_render();
    
    /*
     * Do not touch the code below as they serve the purpose for
     * closing the window.
     */
    if (Util::Input::IsKeyUp(Util::Keycode::ESCAPE) ||
        Util::Input::IfExit()) {
        m_CurrentState = State::END;
    }
}

void App::End() { // NOLINT(this method will mutate members in the future)
    LOG_TRACE("End");
}
