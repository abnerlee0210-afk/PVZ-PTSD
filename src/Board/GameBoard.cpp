#include "Board/GameBoard.hpp"

#include <limits>
#include <cmath>
#include <vector>
#include <memory>

#include "Entity/Plant.hpp"
#include "Entity/Zombie.hpp"
#include "Entity/CherryBomb.hpp"
#include "Entity/ExplosionEffect.hpp"

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

    if (bestRow == -1 || bestCol == -1) return false;

    // 容許範圍：避免點太遠也被吸進格子
    if (bestRowDist > 60.0f || bestColDist > 60.0f) return false;

    row = bestRow;
    col = bestCol;
    return true;
}

bool GameBoard::IsCellEmpty(int row, int col) const {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) return false;
    return m_Grid[row][col] == nullptr;
}

void GameBoard::PlacePlant(Plant* plant, int row, int col) {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) return;
    m_Grid[row][col] = plant;
}

void GameBoard::RemovePlant(int row, int col) {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) return;
    m_Grid[row][col] = nullptr;
}

Plant* GameBoard::GetPlant(int row, int col) const {
    if (row < 0 || row >= m_Rows || col < 0 || col >= m_Cols) return nullptr;
    return m_Grid[row][col];
}

void GameBoard::Update(const std::vector<std::shared_ptr<Zombie>>& zombies) {
    // 1. 更新並清理已過期的特效
    for (auto it = m_Effects.begin(); it != m_Effects.end(); ) {
        (*it)->Update();
        if ((*it)->IsFinished()) {
            it = m_Effects.erase(it);
        } else {
            ++it;
        }
    }

    // 2. 櫻桃炸彈爆炸判定
    for (int r = 0; r < m_Rows; ++r) {
        for (int c = 0; c < m_Cols; ++c) {
            Plant* plant = m_Grid[r][c];
            if (!plant) continue;

            CherryBomb* cherry = dynamic_cast<CherryBomb*>(plant);
            // 當櫻桃炸彈計時結束 (IsExploded)
            if (cherry && cherry->IsExploded()) {
                glm::vec2 explodePos = cherry->GetTransform().translation;

                // 產生視覺特效
                m_Effects.push_back(std::make_shared<ExplosionEffect>(explodePos));

                // 3. 九宮格傷害邏輯：遍歷所有殭屍
                for (auto& zombie : zombies) {
                    if (!zombie->IsAlive()) continue;

                    glm::vec2 zombiePos = zombie->GetTransform().translation;
                    float dist = glm::distance(explodePos, zombiePos);

                    // 150.0f 的半徑足以覆蓋 3x3 的範圍
                    if (dist < cherry->GetExplosionRadius()) {
                        // 給予極大傷害，殭屍會直接進入死亡或消失狀態
                        zombie->TakeDamage(4000);
                    }
                }

                // 櫻桃炸彈炸完後從格子移除
                m_Grid[r][c] = nullptr;
                cherry->Destroy(); // 標記為死亡，讓 Scene 釋放
                cherry->SetAlive(false);
            }
        }
    }
}

void GameBoard::Draw() {
    // 畫出所有爆炸特效
    for (auto& effect : m_Effects) {
        effect->Draw();
    }
}