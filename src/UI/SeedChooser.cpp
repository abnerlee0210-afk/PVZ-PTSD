//
// Created by hankl on 2026/4/7.
//
#include "UI/SeedChooser.hpp"

SeedChooser::SeedChooser(const glm::vec2& position)
    : m_Position(position) {

    m_BackgroundObject = std::make_shared<BackgroundImage>(bgPath);
    m_BackgroundObject->m_Transform.translation = position;

    m_SunText = std::make_shared<Text>("150",15);
    m_SunText->m_Transform.translation = (m_Position - glm::vec2(215.0f, 30.0f));
}

void SeedChooser::AddCard(const std::shared_ptr<SeedCard>& card) {
    m_Cards.push_back(card);
}

void SeedChooser::LayoutCards() {
    float startX = m_Position.x - 160.0f;
    float y = m_Position.y ;
    float spacing = 55.0f;

    for (int i = 0; i < static_cast<int>(m_Cards.size()); ++i) {
        m_Cards[i]->m_Transform.translation = {
            startX + i * spacing,
            y
        };
    }
}

bool SeedChooser::TrySelectCard(const glm::vec2& mousePos) {
    for (int i = 0; i < static_cast<int>(m_Cards.size()); ++i) {
        if (m_Cards[i]->ContainsPoint(mousePos)) {
            LOG_DEBUG("CHOOSE {} CARD", i + 1);
            m_SelectedIndex = i;

            for (int j = 0; j < static_cast<int>(m_Cards.size()); ++j) {
                m_Cards[j]->SetSelected(j == m_SelectedIndex);
            }
            return true;
        }
    }
    return false;
}

PlantType SeedChooser::GetSelectedPlantType() const {
    if (m_SelectedIndex < 0 || m_SelectedIndex >= static_cast<int>(m_Cards.size())) {
        return PlantType::PEASHOOTER; // 保底
    }
    return m_Cards[m_SelectedIndex]->GetPlantType();
}

bool SeedChooser::HasSelection() const {
    return m_SelectedIndex >= 0;
}

void SeedChooser::UpdateSun(int sunCount) {
    if (m_SunText) {
        m_SunText->SetText(std::to_string(sunCount));
    }
}