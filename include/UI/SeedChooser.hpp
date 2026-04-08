//
// Created by hankl on 2026/4/7.
//

#ifndef SEEDCHOOSER_HPP
#define SEEDCHOOSER_HPP

#include "pch.hpp"

#include "Screen/BackgroundImage.hpp"
#include "Screen/Text.hpp"

#include "Level/LevelTypes.hpp"
#include "UI/SeedCard.hpp"
#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class SeedChooser {
public:
    explicit SeedChooser(const glm::vec2& position);

    void AddCard(const std::shared_ptr<SeedCard>& card);
    void LayoutCards();

    bool TrySelectCard(const glm::vec2& mousePos);
    PlantType GetSelectedPlantType() const;
    bool HasSelection() const;

    void UpdateSun(int sunCount);


    std::shared_ptr<BackgroundImage> GetBackgroundObject() const { return m_BackgroundObject; }
    const std::vector<std::shared_ptr<SeedCard>>& GetCards() const { return m_Cards; }
    std::shared_ptr<Text> GetSunText() const { return m_SunText; }

private:
    glm::vec2 m_Position;
    std::shared_ptr<BackgroundImage> m_BackgroundObject;
    std::shared_ptr<Text> m_SunText;
    std::vector<std::shared_ptr<SeedCard>> m_Cards;

    std::string bgPath = RESOURCE_DIR "/graphics/Screen/ChooserBackground.png";

    int m_SelectedIndex = -1;
};

#endif //SEEDCHOOSER_HPP
