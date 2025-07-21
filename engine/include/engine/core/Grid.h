#pragma once

#include <vector>

#include "Cell.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


class Grid {
public:
    Grid(int width, int height, float cellSize);

    Cell& GetCell(int x, int y);
    const Cell& GetCell(int x, int y) const;

     Cell& GetCellAtPos(const glm::vec3& worldPos);
    const Cell& Grid::GetCellAtPos(const glm::vec3& worldPos) const;
    std::vector<Cell*> Grid::GetCellsAtPoints(const std::vector<glm::vec3>& points);
    std::vector<Cell*> GetNeighbors(int x, int y);
    std::vector<Cell> getAllCells() const;

    void SetPath(const std::vector<glm::ivec2>& pathCells);

    int GetCols() const { return cols; }
    int GetRows() const { return rows; }
    float GetCellSize() const { return cellSize; }

private:
    int width;
    int height;
    float cellSize;
    int cols;
    int rows;

    std::vector<std::vector<Cell>> cells;
};
