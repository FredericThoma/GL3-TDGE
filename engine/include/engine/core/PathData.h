#include "engine/ecs/components/GridPosition.h"

struct PathData {
    std::vector<GridPosition> points;

    const GridPosition& at(std::size_t index) const {
        return points.at(index);
    }

    std::size_t length() const {
        return points.size();
    }
};
