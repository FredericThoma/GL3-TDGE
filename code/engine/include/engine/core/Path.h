#pragma once
#include <unordered_map>
#include <vector>
#include "Grid.h"
#include "glm/vec3.hpp"

class Path {
public:
    Path();
    Path(const std::vector<glm::vec2>& cellIndices, Grid& grid);
    int getPathSegmentCount() const;
    [[nodiscard]] std::vector<glm::vec3> getPoints() const;
    const Cell* getCellByPathSegmentIndex(int segmentIndex) const;
    [[nodiscard]] std::vector<Cell*> getCells() const;
    void buildCellIndices();

private:
    std::vector<glm::vec3> points;
    std::vector<Cell*> cells;
    std::unordered_map<int, int> cellIDToIndex;
    Grid* grid;
    std::list<Cell*> cellListOrdered;
};
