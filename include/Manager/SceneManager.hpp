//
// Created by 李政翰 on 2026/4/3.
//

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include "Scene/Scene.hpp"
#include "Util/Logger.hpp"

class SceneManager {
public:
    /**
     * @brief 定義遊戲中所有的場景類型
     */
    enum class SceneType {
        MENU,
        SELECT,
        GAME,
        // 未來可以在這裡輕鬆新增：SETTINGS, CREDITS...
    };

    SceneManager();
    ~SceneManager();

    /**
     * @brief 將場景實體註冊到管理器中
     * @param type 場景標籤 (例如 SceneType::MENU)
     * @param scene 場景的 shared_ptr 實體
     */
    void AddScene(SceneType type, std::shared_ptr<Scene> scene) {
        if (scene) {
            m_Scenes[type] = scene;
        } else {
            LOG_ERROR("試圖註冊一個空的場景指標！");
        }
    }
    // 遊戲啟動時，你會把所有場景先丟進這個管理器的「倉庫」裡。

    /**
     * @brief 切換目前執行的場景
     * @param type 要切換到的目標場景標籤
     */
    void switch_to(SceneType type);

    /**
     * @brief 每一幀更新目前場景的邏輯
     */
    void on_update();

    /**
     * @brief 每一幀渲染目前場景的畫面
     */
    void on_render();

    /**
     * @brief 當程式結束時呼叫，確保目前場景安全退出
     */
    void on_exit();

private:
    /**
     * @brief 儲存所有已註冊的場景，由 SceneType 對應其 shared_ptr
     */
    std::map<SceneType, std::shared_ptr<Scene>> m_Scenes; // 這是一個鍵值對容器，把 SceneType (標籤) 對應到 shared_ptr<Scene> (實際的場景物件)。

    /**
     * @brief 指向目前正在運行的場景
     * 改用 shared_ptr 避免指標失效造成的 Crash
     */
    std::shared_ptr<Scene> m_CurrentScene = nullptr;
};

#endif //SCENEMANAGER_HPP
