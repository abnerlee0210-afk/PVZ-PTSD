#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP

#include "pch.hpp" // 引入專案預編譯標頭檔，解決 Util::Time 找不到的問題
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Time.hpp"

class ExplosionEffect : public Util::GameObject {
public:
    ExplosionEffect(const glm::vec2& position) {
        m_Transform.translation = position;
        m_Transform.scale = {1.5f, 1.5f}; // 讓爆炸字樣大一點

        // 讀取你指定的單張 Boom.png 圖片路徑
        SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Plants/Boom.png"));
    }

    // 關鍵修正：必須加上 override 才能正確覆蓋基底類別的虛擬函式
    void Update(){
        m_LifeTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    }

    // 顯示 0.8 秒後銷毀
    bool IsFinished() const { return m_LifeTimer > 0.8f; }

private:
    float m_LifeTimer = 0.0f;
}; // 確保這裡有分號閉合

#endif // EXPLOSIONEFFECT_HPP