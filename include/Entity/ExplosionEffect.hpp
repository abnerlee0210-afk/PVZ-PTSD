#ifndef EXPLOSIONEFFECT_HPP
#define EXPLOSIONEFFECT_HPP

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Time.hpp"

class ExplosionEffect : public Util::GameObject {
public:
    ExplosionEffect(const glm::vec2& position) {
        m_Transform.translation = position;
        m_Transform.scale = {1.5f, 1.5f}; // 讓爆炸字樣大一點
        // 使用你指定的路徑
        SetDrawable(std::make_shared<Util::Image>(RESOURCE_DIR "/graphics/Plants/Boom.png"));
    }

    void Update() {
        m_LifeTimer += Util::Time::GetDeltaTimeMs() / 1000.0f;
    }

    // 顯示 0.8 秒後銷毀
    bool IsFinished() const { return m_LifeTimer > 0.8f; }

private:
    float m_LifeTimer = 0.0f;
};

#endif