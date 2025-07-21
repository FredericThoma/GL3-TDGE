#include "engine/core/Grid.h"

#include <iostream>
#include <stdexcept>
#include <vector>

#include "glm/vec2.hpp"

Grid::Grid(int width, int height, float cellSize)
    : width(width), height(height), cellSize(cellSize) {

    int cols = static_cast<int>(width / cellSize);
    int rows = static_cast<int>(height / cellSize);

    cells.resize(rows, std::vector<Cell>(cols));

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            cells[y][x] = Cell{
                CellType::Empty,
                glm::vec2(x * cellSize, y * cellSize)
            };
        }
    }
}


Cell& Grid::GetCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("GetCell: Index out of range");
    return cells[y][x];
}

std::vector<Cell> Grid::getAllCells() const {
    std::vector<Cell> allCells;
    for (const auto& row : cells) {
        for (const auto& cell : row) {
            allCells.push_back(cell);
            //std::cout << (cell.type == CellType::Path ? "Path" : "Empty") << std::endl;


        }
    }
    return allCells;
}

const Cell& Grid::GetCell(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height)
        throw std::out_of_range("GetCell: Index out of range");
    return cells[y][x];
}

std::vector<Cell>& Grid::GetNeighbors(int x, int y) {
    static std::vector<Cell> neighbors;
    neighbors.clear();

    const int dx[] = { -1, 1, 0, 0 };
    const int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
            neighbors.push_back(cells[ny][nx]);
        }
    }

    return neighbors;
}

void Grid::SetPath(const std::vector<glm::ivec2>& pathCells) {
    int cols = width / cellSize;
    int rows = height / cellSize;

    for (const auto& coord : pathCells) {
        if (coord.x >= 0 && coord.x < cols && coord.y >= 0 && coord.y < rows) {
            cells[coord.y][coord.x].type = CellType::Path;
        }
    }
}

