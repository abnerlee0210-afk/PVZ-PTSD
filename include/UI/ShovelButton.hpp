//
// Created by 李政翰 on 2026/3/18.
//

#ifndef SHOVELBUTTON_HPP
#define SHOVELBUTTON_HPP

#include "../../PTSD/include/pch.hpp"

#include "../../PTSD/include/Util/GameObject.hpp"
#include "../../PTSD/include/Util/Image.hpp"

class ShovelButton : public Util::GameObject {
public:
    ShovelButton(const std::string& imagePath, const glm::vec2& position);

    bool ContainsPoint(const glm::vec2& point) const;

    void SetSelected(bool selected);
    bool IsSelected() const { return m_Selected; }

private:
    bool m_Selected;
    float m_Width;
    float m_Height;
};


#endif //SHOVELBUTTON_HPP