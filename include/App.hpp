#ifndef APP_HPP
#define APP_HPP

#include "pch.hpp" // IWYU pragma: export
#include "Scene/MenuScene.hpp"
#include "Scene/LevelSelectScene.hpp"

class App {
public:
    enum class State {
        START,
        UPDATE,
        END,
    };

    State GetCurrentState() const { return m_CurrentState; }

    void Start();

    void Update();

    void End(); // NOLINT(readability-convert-member-functions-to-static)

private:
    void ValidTask();

private:
    State m_CurrentState = State::START;
    std::shared_ptr<MenuScene> m_MenuScene;
    std::shared_ptr<LevelSelectScene> m_LevelSelectScene;
};

#endif
