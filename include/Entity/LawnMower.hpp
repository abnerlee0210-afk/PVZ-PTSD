//
// Created by hankl on 2026/3/20.
//

#ifndef LAWNMOWER_HPP
#define LAWNMOWER_HPP

#include "pch.hpp"

#include "Util/GameObject.hpp"
#include "Util/Image.hpp"

class LawnMower : public Util::GameObject {
public:
    LawnMower(int row, const glm::vec2& position);

    void Update();

    void Activate();

    int GetRow() const { return m_Row; }

    bool IsActive() const { return m_IsActive; }
    bool IsAlive() const { return m_Alive; }

    void Destroy();

private:
    int m_Row;
    bool m_IsActive;
    bool m_Alive;
    float m_Speed;
};

#endif //LAWNMOWER_HPP