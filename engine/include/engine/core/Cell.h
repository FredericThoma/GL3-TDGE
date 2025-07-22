#pragma once

#include <string>

#include "glm/vec3.hpp"

enum class CellType {
    Empty,
    Path,
    Buildable,
    Blocked
};

inline std::string to_string(CellType type) {
    switch (type) {
    case CellType::Empty:     return "Empty";
    case CellType::Path:      return "Path";
    case CellType::Buildable: return "Buildable";
    case CellType::Blocked:   return "Blocked";
    default:                  return "Unknown";
    }
}

struct Cell {
    CellType type;
    glm::vec3 worldPosition;
    int size;
    int id;
    bool visited = false;
    Cell(CellType type = CellType::Empty, const glm::vec3& worldPosition = glm::vec3(0.0f), int id = 0, int cellSize = 10)
       : type(type), worldPosition(worldPosition), id(id), size(cellSize) {}

    glm::vec3 getWorldPositionCenter() const
    {
        float halfSize = static_cast<float>(size) / 2.0f;
        return worldPosition + glm::vec3(-halfSize, -halfSize, 0.0f);
    }

};
