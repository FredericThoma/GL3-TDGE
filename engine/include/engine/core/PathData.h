#include "Grid.h"

struct PathData {
    glm::vec3 points;
    Grid* grid = nullptr;
    std::vector<Cell*> cells;

    void setCells()
    {
        cells.clear();

        if (!grid) return;

        for (const auto& p : points)
        {
            if (Cell* cell = grid->GetCellAtPos(p))
                cells.push_back(cell);
        }

    }
};
