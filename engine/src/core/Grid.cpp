#include "engine/core/Grid.h"

#include <stdexcept>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

Grid::Grid(int width, int height, float cellSize)
    : width(width), height(height), cellSize(cellSize)
{
    cols = static_cast<int>(width / cellSize);
    rows = static_cast<int>(height / cellSize);

    cells.resize(rows, std::vector<Cell>(cols));

    int idCounter = 0;
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            glm::vec3 position(x * cellSize, y * cellSize, 0.0f);
            cells[y][x] = Cell(CellType::Empty, position, idCounter++, cellSize);
        }
    }
}

Cell* Grid::GetCell(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        throw std::out_of_range("GetCell: Index out of range");
    return &cells[y][x];
}

Cell* Grid::GetCellByCellId(int cellID)
{
    int x = cellID / cols;
    int y = cellID % cols;
    return GetCell(x, y);
}

std::vector<Cell*> Grid::GetCellsAtPoints(const std::vector<glm::vec3>& points) {
    std::vector<Cell*> cells;
    cells.reserve(points.size());

    for (const auto& p : points) {
        Cell* cell = GetCellAtPos(p);
        cells.push_back(cell);
    }

    return cells;
}

std::vector<Cell*> Grid::GetCellsAtIndices(const std::vector<glm::vec2>& cellIndices) {
    std::vector<Cell*> cells;
    cells.reserve(cellIndices.size());

    for (const auto& i : cellIndices) {
        Cell* cell = GetCell(i.x, i.y);
        cells.push_back(cell);
    }

    return cells;
}

const Cell* Grid::GetCell(int x, int y) const {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        throw std::out_of_range("GetCell: Index out of range");
    return &cells[y][x];
}

std::vector<Cell*> Grid::GetNeighbors(Cell* cell) {
    std::vector<Cell*> neighbors;
    auto indices = CellPositionToIndex(cell); // returns {x, y}
    int x = indices.x;
    int y = indices.y;

    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
            neighbors.push_back(&cells[ny][nx]); // cells[row][column]
        }
    }

    return neighbors;
}


std::vector<glm::vec3> Grid::GetPositionOfCells(const std::vector<glm::vec2>& cellIndices)
{
    std::vector<glm::vec3> positions;
    for (const auto& cellIndex : cellIndices)
    {
        auto cell = GetCell(cellIndex.x, cellIndex.y);
        positions.push_back(cell->worldPosition);
    }
    return positions;
}

Cell* Grid::GetCellAtPos(const glm::vec3& worldPos) {
    int x = static_cast<int>(worldPos.x / cellSize);
    int y = static_cast<int>(worldPos.y / cellSize);
    return GetCell(x, y);
}

const Cell* Grid::GetCellAtPos(const glm::vec3& worldPos) const {
    int x = static_cast<int>(worldPos.x / cellSize);
    int y = static_cast<int>(worldPos.y / cellSize);
    return GetCell(x, y);
}


std::vector<Cell*> Grid::getAllCells() const {
    std::vector<Cell*> allCells;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            allCells.push_back(const_cast<Cell*>(&cell));
        }
    }
    return allCells;
}

void Grid::MarkPathCells(const std::vector<glm::vec2>& pathIndices) {
    for (const auto& position : pathIndices) {
        auto cell = GetCell(position.x, position.y);
        cell->type = CellType::Path;
    }
}
