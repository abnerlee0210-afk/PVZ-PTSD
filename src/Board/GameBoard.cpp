#include "Board/GameBoard.hpp"

#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "Entity/CherryBomb.hpp"
#include "Entity/ExplosionEffect.hpp"
#include "Entity/Plant.hpp"
#include "Entity/Zombie.hpp"

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
        const float dist = std::abs(y - m_RowCenters[r]);
        if (dist < bestRowDist) {
            bestRowDist = dist;
            bestRow = r;
        }
    }

    for (int c = 0; c < m_Cols; ++c) {
        const float dist = std::abs(x - m_ColCenters[c]);
        if (dist < bestColDist) {
            bestColDist = dist;
            bestCol = c;
        }
    }

    if (bestRow == -1 || bestCol == -1) {
        return false;
    }

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

int GameBoard::GetNearestColumn(float x) const {
    if (m_ColCenters.empty()) {
        return -1;
    }

    int bestCol = -1;
    float bestDist = std::numeric_limits<float>::max();
    for (int c = 0; c < m_Cols; ++c) {
        const float dist = std::abs(x - m_ColCenters[c]);
        if (dist < bestDist) {
            bestDist = dist;
            bestCol = c;
        }
    }

    return bestCol;
}

bool GameBoard::IsZombieInsideCherryBombArea(
    const CherryBomb& cherry,
    const Zombie& zombie,
    const glm::vec2& explosionCenter
) const {
    const int zombieCol = GetNearestColumn(zombie.GetTransform().translation.x);
    if (zombieCol < 0) {
        return false;
    }

    if (std::abs(zombie.GetRow() - cherry.GetRow()) > 1) {
        return false;
    }

    if (std::abs(zombieCol - cherry.GetCol()) > 1) {
        return false;
    }

    const glm::vec2 zombiePos = zombie.GetTransform().translation;
    return glm::distance(explosionCenter, zombiePos) <= cherry.GetExplosionRadius();
}

void GameBoard::Update(const std::vector<std::shared_ptr<Zombie>>& zombies) {
    for (auto it = m_Effects.begin(); it != m_Effects.end(); ) {
        (*it)->Update();
        if ((*it)->IsFinished()) {
            it = m_Effects.erase(it);
        } else {
            ++it;
        }
    }

    for (int row = 0; row < m_Rows; ++row) {
        for (int col = 0; col < m_Cols; ++col) {
            Plant* plant = m_Grid[row][col];
            if (!plant) {
                continue;
            }

            auto* cherry = dynamic_cast<CherryBomb*>(plant);
            if (!cherry || !cherry->IsExploded()) {
                continue;
            }

            const glm::vec2 explosionCenter = cherry->GetTransform().translation;
            m_Effects.push_back(std::make_shared<ExplosionEffect>(explosionCenter));

            for (const auto& zombie : zombies) {
                if (!zombie || !zombie->IsAlive()) {
                    continue;
                }

                if (IsZombieInsideCherryBombArea(*cherry, *zombie, explosionCenter)) {
                    zombie->TakeDamage(99999, true);
                }
            }

            cherry->SetAlive(false);
            m_Grid[row][col] = nullptr;
        }
    }
}

void GameBoard::Draw() {
    for (const auto& effect : m_Effects) {
        effect->Draw();
    }
}
