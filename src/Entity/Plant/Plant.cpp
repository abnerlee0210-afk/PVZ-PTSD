//
// Created by hankl on 2026/3/10.
//
#include "Entity/Plant/Plant.hpp"
#include "Render/RenderLayer.hpp"
#include "Render/RenderLayer.hpp"

Plant::Plant(const std::string& imagePath,
             int row,
             int col,
             const glm::vec2& position,
             int hp,
             int cost)
    : Util::GameObject(std::make_shared<Util::Image>(imagePath), RenderLayer::PLANT_BASE),
      m_Row(row),
      m_Col(col),
      m_HP(hp),
      m_Cost(cost),
      m_Alive(true) {
    m_Transform.translation = position;
}

void Plant::TakeDamage(int damage) {
    if (!m_Alive) {
        return;
    }

    m_HP -= damage;
    if (m_HP <= 0) {
        m_HP = 0;
        m_Alive = false;
    }
}

void Plant::UpdateZIndexByY() {
    SetZIndex(RenderLayer::WorldYSort(RenderLayer::PLANT_BASE, m_Transform.translation.y));
}

void Plant::ScheduleProjectiles() {
    m_ScheduledProjectileTimers = GetProjectileFireDelays();
}

void Plant::UpdateScheduledProjectiles(float deltaTime) {
    for (auto& timer : m_ScheduledProjectileTimers) {
        timer -= deltaTime;
    }
}

bool Plant::HasPendingProjectiles() const {
    return !m_ScheduledProjectileTimers.empty();
}

bool Plant::HasScheduledProjectileReady() const {
    for (float timer : m_ScheduledProjectileTimers) {
        if (timer <= 0.0f) {
            return true;
        }
    }
    return false;
}

void Plant::ConsumeScheduledProjectile() {
    auto it = std::find_if(
        m_ScheduledProjectileTimers.begin(),
        m_ScheduledProjectileTimers.end(),
        [](float timer) {
            return timer <= 0.0f;
        }
    );

    if (it != m_ScheduledProjectileTimers.end()) {
        m_ScheduledProjectileTimers.erase(it);
    }
}