//
// Created by hankl on 2026/3/10.
//

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "pch.hpp"

#include "Board/BoardLayout.hpp"

class Plant; // 前向聲明 (Forward Declaration)，告訴編譯器有 Plant 這個類別，減少編譯相依性

class GameBoard {
public:
    GameBoard(int rows, int cols, const BoardLayout& layout); // 建構子

    bool ScreenToGrid(float x, float y, int& row, int& col) const;  // 螢幕座標轉網格索引
    glm::vec2 GetCellCenter(int row, int col) const;                // 網格索引轉中心點座標

    bool IsCellEmpty(int row, int col) const;                       // 檢查該格是否有植物
    void PlacePlant(Plant* plant, int row, int col);                // 在指定格放置植物
    Plant* GetPlant(int row, int col) const;                        // 取得指定格的植物指標
    void RemovePlant(int row, int col);                             // 移除指定格的植物

    int GetRows() const { return m_Rows; }
    int GetCols() const { return m_Cols; }

private:
    int m_Rows;
    int m_Cols;

    std::vector<float> m_RowCenters;
    std::vector<float> m_ColCenters;


    std::vector<std::vector<Plant*>> m_Grid;
};


#endif //GAMEBOARD_HPP