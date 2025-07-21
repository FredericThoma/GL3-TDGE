#pragma once

#include <vector>
#include "engine/core/Cell.h"
#include "glm/vec2.hpp"

class Grid {
public:
    Grid() = default;
    Grid(int width, int height, float cellSize);
    std::vector<Cell> getAllCells() const;
    Cell& GetCell(int x, int y);
    const Cell& GetCell(int x, int y) const;

    std::vector<Cell>& GetNeighbors(int x, int y); // Optional für Pfadsuche

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    float getCellSize() const { return cellSize; }
    void SetPath(const std::vector<glm::ivec2>& pathCells);

private:
    int width;
    int height;
    float cellSize;
    std::vector<std::vector<Cell>> cells;
};
