//
// Created by hankl on 2026/5/31.
//
#include "UI/ChoosePlantPanel.hpp"

#include "Factory/SeedCardFactory.hpp"
#include "Util/Logger.hpp"

ChoosePlantPanel::ChoosePlantPanel(
    const std::vector<PlantType>& availablePlants,
    int maxChoosePlants
)
    : m_AvailablePlants(availablePlants),
      m_MaxChoosePlants(maxChoosePlants) {
}

void ChoosePlantPanel::Create(Util::Renderer& root) {
    if (m_Created) {
        return;
    }

    m_Background = std::make_shared<BackgroundImage>(m_BackgroundPath);
    m_Background->m_Transform.translation = {0.0f, 0.0f};
    root.AddChild(m_Background);

    float startX = -185.0f;
    float startY = 185.0f;
    float spacingX = 53.0f;
    float spacingY = 72.0f;

    for (int i = 0; i < static_cast<int>(m_AvailablePlants.size()); ++i) {
        int row = i / 7;
        int col = i % 7;

        glm::vec2 pos = {
            startX + col * spacingX,
            startY - row * spacingY
        };

        auto card = SeedCardFactory::CreateSeedCard(
            m_AvailablePlants[i],
            pos
        );

        if (!card) {
            continue;
        }

        m_Cards.push_back(card);
        root.AddChild(card);

        if (card->GetOuterFrame()) {
            root.AddChild(card->GetOuterFrame());
        }

        card->SyncDecorationsPosition();
    }

    // 如果你目前沒有 Button 圖，可以先晚點做，先用 Enter 開始
    m_Created = true;
}

void ChoosePlantPanel::Destroy(Util::Renderer& root) {
    for (auto& card : m_Cards) {
        if (!card) {
            continue;
        }

        if (card->GetOuterFrame()) {
            root.RemoveChild(card->GetOuterFrame());
        }

        if (card->GetCooldownOverlay()) {
            root.RemoveChild(card->GetCooldownOverlay());
        }

        root.RemoveChild(card);
    }

    m_Cards.clear();
    m_SelectedPlants.clear();

    if (m_StartButton) {
        root.RemoveChild(m_StartButton);
        m_StartButton = nullptr;
    }

    if (m_Background) {
        root.RemoveChild(m_Background);
        m_Background = nullptr;
    }
    m_Created = false;
    m_StartRequested = false;
}

void ChoosePlantPanel::HandleClick(const glm::vec2& mousePos) {
    for (auto& card : m_Cards) {
        if (!card) {
            continue;
        }

        if (card->ContainsPoint(mousePos)) {
            TogglePlant(card->GetPlantType());
            return;
        }
    }
}

void ChoosePlantPanel::TogglePlant(PlantType type) {
    if (IsChosen(type)) {
        m_SelectedPlants.erase(
            std::remove(m_SelectedPlants.begin(), m_SelectedPlants.end(), type),
            m_SelectedPlants.end()
        );
    }
    else {
        if (static_cast<int>(m_SelectedPlants.size()) >= m_MaxChoosePlants) {
            LOG_DEBUG("ChoosePlantPanel full");
            return;
        }

        m_SelectedPlants.push_back(type);
    }

    UpdateCardSelectionVisual();
}

bool ChoosePlantPanel::IsChosen(PlantType type) const {
    return std::find(
        m_SelectedPlants.begin(),
        m_SelectedPlants.end(),
        type
    ) != m_SelectedPlants.end();
}

void ChoosePlantPanel::UpdateCardSelectionVisual() {
    for (auto& card : m_Cards) {
        if (!card) {
            continue;
        }

        card->SetSelected(IsChosen(card->GetPlantType()));
    }
}


bool ChoosePlantPanel::IsReadyToStart() const {
    return static_cast<int>(m_SelectedPlants.size()) == m_MaxChoosePlants;
}

const std::vector<PlantType>& ChoosePlantPanel::GetSelectedPlants() const {
    return m_SelectedPlants;
}

