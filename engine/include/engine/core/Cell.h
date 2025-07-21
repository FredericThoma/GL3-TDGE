#pragma once

#include "glm/vec3.hpp"

enum class CellType {
    Empty,
    Path,
    Buildable,
    Blocked
};

struct Cell {
    CellType type;
    glm::vec3 worldPosition;
    int id;

    Cell(CellType type = CellType::Empty, const glm::vec3& worldPosition = glm::vec3(0.0f), int id = 0)
       : type(type), worldPosition(worldPosition), id(id) {}
};
