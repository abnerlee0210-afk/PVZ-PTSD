//
// Created by hankl on 2026/3/10.
//

#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "pch.hpp"

class Plant; // 前向聲明 (Forward Declaration)，告訴編譯器有 Plant 這個類別，減少編譯相依性

class GameBoard {
public:
    GameBoard(int rows, int cols, float startX, float startY); // 建構子

    bool ScreenToGrid(float x, float y, int& row, int& col) const;  // 螢幕座標轉網格索引
    glm::vec2 GridToScreen(int row, int col) const;                 // 網格索引轉螢幕左下角座標
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
    float m_GridStartX;     // 棋盤左下角的 X 座標
    float m_GridStartY;     // 棋盤左下角的 Y 座標
    float m_CellWidth;      // 每一格的寬度
    float m_CellHeight;     // 每一格的高度

    std::vector<std::vector<Plant*>> m_Grid;
};


#endif //GAMEBOARD_HPP