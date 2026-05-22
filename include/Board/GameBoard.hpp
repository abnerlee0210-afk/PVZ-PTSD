#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include <vector>
#include <memory>
#include <glm/vec2.hpp>
#include "Entity/Zombie.hpp"
#include "Entity/ExplosionEffect.hpp" // 必須包含，否則 m_Effects 報錯
#include "Board/BoardLayout.hpp"

class CherryBomb;
class Plant;

class GameBoard {
public:
    GameBoard(int rows, int cols, const BoardLayout& layout);
    bool ScreenToGrid(float x, float y, int& row, int& col) const;
    glm::vec2 GetCellCenter(int row, int col) const;
    bool IsCellEmpty(int row, int col) const;
    void PlacePlant(Plant* plant, int row, int col);
    void RemovePlant(int row, int col);
    Plant* GetPlant(int row, int col) const;

    // 更新與繪製
    void Update(const std::vector<std::shared_ptr<Zombie>>& zombies);
    void Draw();

private:
    int m_Rows;
    int m_Cols;
    std::vector<float> m_RowCenters;
    std::vector<float> m_ColCenters;
    std::vector<std::vector<Plant*>> m_Grid;

    // 管理場上所有爆炸特效
    std::vector<std::shared_ptr<ExplosionEffect>> m_Effects;

    int GetNearestColumn(float x) const;
    bool IsZombieInsideCherryBombArea(
        const CherryBomb& cherry,
        const Zombie& zombie,
        const glm::vec2& explosionCenter
    ) const;
};

#endif
