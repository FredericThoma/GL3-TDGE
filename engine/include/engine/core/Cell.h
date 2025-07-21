#pragma once

#include "glm/vec2.hpp"

enum class CellType {
    Empty,
    Path,
    Buildable,
    Blocked
};

struct Cell {
    CellType type = CellType::Empty;
    glm::vec2 worldPosition;
    int gridX;
    int gridY;
};
