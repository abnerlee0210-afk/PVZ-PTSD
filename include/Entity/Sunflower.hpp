//
// Created by hankl on 2026/3/13.
//

#ifndef SUNFLOWER_HPP
#define SUNFLOWER_HPP

#include "Entity/Plant.hpp"

class Sunflower : public Plant {
public:
    Sunflower(int row, int col, const glm::vec2& position);

    void Update() override;

    bool CanGenerateSun() const override;
    glm::vec2 GetSunSpawnPosition() const override;
    void ResetSunTimer() override;

protected:
    void InitAnimations() override;

private:
    float m_GenerateSunTimer;
    float m_GenerateSunInterval;
};

#endif // SUNFLOWER_HPP