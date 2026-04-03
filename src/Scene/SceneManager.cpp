//
// Created by 李政翰 on 2026/4/3.
//
#include "Scene/SceneManager.hpp"

/**
 * 建構子與解構子
 */
SceneManager::SceneManager() {
    LOG_DEBUG("SceneManager Constructor");
}

SceneManager::~SceneManager() {
    LOG_DEBUG("SceneManager Destructor");
}



/**
 * 切換場景邏輯
 */
void SceneManager::switch_to(SceneType type) {
    // 1. 在 Map 中尋找目標場景類型
    auto it = m_Scenes.find(type);

    // 2. 防呆：如果該場景類型尚未被 AddScene 註冊，則停止切換
    if (it == m_Scenes.end()) {
        LOG_ERROR("Cannot switch to scene: Scene type not registered!");
        return;
    }

    // 3. 獲取目標場景的 shared_ptr
    std::shared_ptr<Scene> next_scene = it->second;

    // 4. 如果目前已經在這個場景，就不用重複進入 (避免資源重複載入)
    if (m_CurrentScene == next_scene) {
        return;
    }

    // 5. 如果目前有正在執行的場景，呼叫其退出函式 (on_exit)
    if (m_CurrentScene) {
        LOG_DEBUG("Exiting current scene...");
        m_CurrentScene->on_exit();
    }

    // 6. 正式切換指標
    m_CurrentScene = next_scene;

    // 7. 呼叫新場景的進入函式 (on_enter)
    if (m_CurrentScene) {
        LOG_DEBUG("Entering new scene...");
        m_CurrentScene->on_enter();
    }
}

/**
 * 每幀更新與渲染的委派 (Delegation)
 */
void SceneManager::on_update() {
    if (m_CurrentScene) {
        m_CurrentScene->on_update();
    }
}

void SceneManager::on_render() {
    if (m_CurrentScene) {
        m_CurrentScene->on_render();
    }
}

 /**
 * 程式關閉時的清理
 */
void SceneManager::on_exit() {
    if (m_CurrentScene) {
        m_CurrentScene->on_exit();
        m_CurrentScene = nullptr; // 清空指標，讓計數器減少
    }
    m_Scenes.clear(); // 清空場景庫
}


// void SceneManager::set_current_scene(std::shared_ptr<Scene> scene) {
//     current_scene = scene.get();
//     if (current_scene)
//         current_scene->on_enter();
// }