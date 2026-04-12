//
// Created by hankl on 2026/3/13.
//

#ifndef SEEDCARD_HPP
#define SEEDCARD_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

#include "Screen/Text.hpp"
#include "Level/LevelTypes.hpp"

class SeedCard : public Util::GameObject {
public:
    SeedCard(const std::string& imagePath,
             PlantType plantType,
             int cost,
             float cooldown,
             const glm::vec2& position);

    PlantType GetPlantType() const { return m_PlantType; }
    int GetCost() const { return m_Cost; }

    bool ContainsPoint(const glm::vec2& point) const;

    void SetSelected(bool selected);
    bool IsSelected() const { return m_Selected; }

    bool IsCoolingDown(float currentTime) const;
    bool IsUsable(int currentSunPoints, float currentTime) const;
    void TriggerCooldown(float currentTime);

    float GetRemainingCooldown(float currentTime) const;

    // 將卡片顯示縮放乘上一個因子（例如 0.9 / 1.1）
    void SetVisualScaleFactor(float factor);

    void SyncDecorationsPosition();
    void UpdateVisualState(int currentSunPoints, float currentTime);


    std::shared_ptr<Util::GameObject> GetOuterFrame() const {return m_OuterFrame;}
    std::shared_ptr<Util::GameObject> GetCooldownOverlay() const {return  m_CooldownOverlay;}
    std::shared_ptr<Util::GameObject> GetCooldownText() const {return m_CooldownText;}

private:
    PlantType m_PlantType;
    int m_Cost;
    bool m_Selected;

    float m_Cooldown;
    float m_LastUsedTime;

    float m_Width;
    float m_Height;

    std::shared_ptr<Util::GameObject> m_OuterFrame; // 被選擇時的外框特效
    std::shared_ptr<Util::GameObject> m_CooldownOverlay; // 冷卻時的遮罩
    std::shared_ptr<Text> m_CooldownText;

    glm::vec2 m_BaseScale {1.0f, 1.0f};
};

#endif //SEEDCARD_HPP