#pragma once

#include "engine/core/Path.h"
#include "engine/core/PathData.h"

struct PathFollow {
    Path* path = nullptr;
    glm::vec3 getTargetPosition(const glm::vec3& currentPosition)
    {
        return path->getTargetPosition(currentPosition);
    }
};
