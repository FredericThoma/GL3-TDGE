#pragma once

#include <vector>

#include "Cell.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"


class Grid {
public:
    Grid(int width, int height, float cellSize);

    Cell* GetCell(int x, int y);
    const Cell* GetCell(int x, int y) const;

     Cell* GetCellAtPos(const glm::vec3& worldPos);
    const Cell* Grid::GetCellAtPos(const glm::vec3& worldPos) const;
    std::vector<Cell*> Grid::GetCellsAtPoints(const std::vector<glm::vec3>& points);
    std::vector<Cell*> GetNeighbors(Cell* cell);
    std::vector<Cell*> getAllCells() const;
    void MarkPathCells(const std::vector<glm::vec2>& pathIndices);
    std::vector<Cell*> Grid::GetCellsAtIndices(const std::vector<glm::vec2>& cellIndices) ;
    std::vector<glm::vec3> Grid::GetPositionOfCells(const std::vector<glm::vec2>& cellIndices);
    int GetCols() const { return cols; }
    int GetRows() const { return rows; }
    Cell* GetCellByCellId(int cellID);
    float GetCellSize() const { return cellSize; }
    glm::vec2 CellPositionToIndex(const Cell* cell) const
    {
        auto pos = cell->worldPosition;
        return glm::vec2(pos.x / cellSize, pos.y / cellSize);
    };


private:
    int width;
    int height;
    float cellSize;
    int cols;
    int rows;

    std::vector<std::vector<Cell>> cells;
};
