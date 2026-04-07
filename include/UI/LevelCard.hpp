//
// Created by 李政翰 on 2026/4/1.
//

#ifndef LEVEL_CARD_HPP
#define LEVEL_CARD_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"
#include "Util/Text.hpp"
#include "Util/Input.hpp"
#include "functional"
#include <iostream>

class LevelCard : public Util::GameObject {
public:
    LevelCard(int levelId,
              const std::string& imagePath,
              const glm::vec2& position
              );

    void SetPosition(const glm::vec2& position);
    glm::vec2 GetPosition() const { return m_Position; }

    void SetSelected(bool selected);
    bool IsSelected() const { return m_Selected; }

    int GetLevelId() const { return m_LevelId; }


    std::shared_ptr<Util::GameObject> GetImageObject() const { return m_ImageObject; }

private:
    int m_LevelId;
    bool m_Selected;

    glm::vec2 m_Position;

    std::shared_ptr<Util::GameObject> m_ImageObject;
};

#endif
