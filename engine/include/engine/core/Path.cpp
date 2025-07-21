#include "Path.h"

#include <optional>

Path::Path() : grid(nullptr) {}

Path::Path(const std::vector<glm::vec3>& points, Grid& grid)
    : points(points), grid(&grid) {
    cells = grid.GetCellsAtPoints(points);
   buildCellIndices();

}

void Path::buildCellIndices() {
    cellIDToIndex.clear();
    for (int i = 0; i < cells.size(); ++i) {
        cellIDToIndex[cells[i]->id] = i;
    }
}

glm::vec3 Path::getTargetPosition(const glm::vec3& currentPosition)
{
    auto current = grid->GetCellAtPos(currentPosition);
    return getNextCell(current)->worldPosition;
}

std::vector<glm::vec3> Path::getPoints() const {
    return points;
}

std::vector<Cell*> Path::getCells() const {
    return cells;
}

const Cell* Path::getNextCell(const Cell& current) const {
    auto indexIt = cellIDToIndex.find(current.id);
    if (indexIt != cellIDToIndex.end()) {
        int index = indexIt->second;
        if (index + 1 < cells.size()) {
            return cells[index + 1];
        }
    }
    return nullptr;
}



