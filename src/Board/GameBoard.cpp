#include "Board/GameBoard.hpp"

#include <limits>
#include <cmath>

#include "Entity/Plant.hpp"

GameBoard::GameBoard(
    int rows,
    int cols,
    const BoardLayout& layout
)
    : m_Rows(rows),
      m_Cols(cols),
      m_RowCenters(layout.rowCenters),
      m_ColCenters(layout.colCenters),
      m_Grid(rows, std::vector<Plant*>(cols, nullptr)) {
}

glm::vec2 GameBoard::GetCellCenter(int row, int col) const {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
        return {0.0f, 0.0f};
    }

    return {m_ColCenters[col], m_RowCenters[row]};
}

bool GameBoard::ScreenToGrid(float x, float y, int& row, int& col) const {
    if (m_RowCenters.empty() || m_ColCenters.empty()) {
        return false;
    }

    int bestRow = -1;
    int bestCol = -1;
    float bestRowDist = std::numeric_limits<float>::max();
    float bestColDist = std::numeric_limits<float>::max();

    for (int r = 0; r < m_Rows; ++r) {
        float dist = std::abs(y - m_RowCenters[r]);
        if (dist < bestRowDist) {
            bestRowDist = dist;
            bestRow = r;
        }
    }

    for (int c = 0; c < m_Cols; ++c) {
        float dist = std::abs(x - m_ColCenters[c]);
        if (dist < bestColDist) {
            bestColDist = dist;
            bestCol = c;
        }
    }

    if (bestRow == -1 || bestCol == -1) {
        return false;
    }

    // 容許範圍：避免點太遠也被吸進格子
    if (bestRowDist > 60.0f || bestColDist > 60.0f) {
        return false;
    }

    row = bestRow;
    col = bestCol;
    return true;
}

bool GameBoard::IsCellEmpty(int row, int col) const {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
        return false;
    }

    return m_Grid[row][col] == nullptr;
}

void GameBoard::PlacePlant(Plant* plant, int row, int col) {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
        return;
    }

    m_Grid[row][col] = plant;
}

void GameBoard::RemovePlant(int row, int col) {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
        return;
    }

    m_Grid[row][col] = nullptr;
}

Plant* GameBoard::GetPlant(int row, int col) const {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) {
        return nullptr;
    }

    return m_Grid[row][col];
}