#pragma once
#include <optional>
#include <unordered_map>
#include <vector>
#include "Grid.h"
#include "glm/vec3.hpp"

class Path {
public:
    Path();
    Path(const std::vector<glm::vec3>& points, Grid& grid);

    std::vector<glm::vec3> getPoints() const;
    std::vector<Cell*> getCells() const;
    const Cell* Path::getNextCell(const Cell& current) const;
    glm::vec3 Path::getTargetPosition(const glm::vec3& currentPosition);
    void buildCellIndices();

private:
    std::vector<glm::vec3> points;
    std::vector<Cell*> cells;
    std::unordered_map<int, int> cellIDToIndex;
    Grid* grid;
};
