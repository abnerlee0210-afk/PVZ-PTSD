//
// Created by hankl on 2026/5/31.
//

#ifndef CHOOSEPLANTPANEL_HPP
#define CHOOSEPLANTPANEL_HPP


#include "pch.hpp"

#include "Level/LevelTypes.hpp"
#include "UI/SeedCard.hpp"
#include "Util/Renderer.hpp"
#include "Screen/BackgroundImage.hpp"
#include "UI/Base/Button.hpp"

class ChoosePlantPanel {
public:
    ChoosePlantPanel(
        const std::vector<PlantType>& availablePlants,
        int maxChoosePlants
    );

    void Create(Util::Renderer& root);
    void Destroy(Util::Renderer& root);

    void HandleClick(const glm::vec2& mousePos);

    bool IsReadyToStart() const;

    const std::vector<PlantType>& GetSelectedPlants() const;

    bool IsStartRequested() const { return m_StartRequested; }

private:
    void TogglePlant(PlantType type);
    bool IsChosen(PlantType type) const;
    void UpdateCardSelectionVisual();

private:
    std::shared_ptr<BackgroundImage> m_Background;
    std::shared_ptr<Button> m_StartButton;

    std::string m_BackgroundPath =
        RESOURCE_DIR "/graphics/Screen/PanelBackground.png";

    std::string m_StartButtonImage =
        RESOURCE_DIR "/graphics/Screen/StartBattleButton.png";

    std::vector<PlantType> m_AvailablePlants;
    std::vector<PlantType> m_SelectedPlants;

    std::vector<std::shared_ptr<SeedCard>> m_Cards;

    int m_MaxChoosePlants = 6;
    bool m_Created = false;
    bool m_StartRequested = false;


};

#endif //CHOOSEPLANTPANEL_HPP
