#include "App.hpp"

#include "Util/Image.hpp"
#include "Util/Input.hpp"
#include "Util/Keycode.hpp"
#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    m_MenuScene = std::make_shared<MenuScene>();
    m_MenuScene->on_enter();

    m_LevelSelectScene = std::make_shared<LevelSelectScene>();
    m_LevelSelectScene->on_enter();

    m_CurrentState = State::UPDATE;
}

void App::Update() {
    if (m_LevelSelectScene != nullptr) {
        m_LevelSelectScene -> on_update();
        m_LevelSelectScene -> on_render();
    }
    //  if (m_MenuScene != nullptr) {
    //     m_MenuScene->on_update();
    //     m_MenuScene->on_render();
    // }
    
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
