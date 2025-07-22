#include "engine/core/Path.h"

Path::Path() : grid(nullptr) {}

Path::Path(const std::vector<glm::vec2>& cellIndices, Grid& grid)
    : grid(&grid) {
    points = grid.GetPositionOfCells(cellIndices);
    cells = grid.GetCellsAtIndices(cellIndices);

   buildCellIndices();
}

void Path::buildCellIndices() {
    cellIDToIndex.clear();
    for (int i = 0; i < cells.size(); ++i) {
        cellIDToIndex[cells[i]->id] = i;
    }
}

const Cell* Path::getCellByPathSegmentIndex(int segmentIndex) const
{
    return cells[segmentIndex];
}

int Path::getPathSegmentCount() const
{
    return cells.size();
}
std::vector<glm::vec3> Path::getPoints() const {
    return points;
}

std::vector<Cell*> Path::getCells() const {
    return cells;
}





