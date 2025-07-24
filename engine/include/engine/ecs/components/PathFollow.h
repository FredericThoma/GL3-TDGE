#pragma once

#include <iostream>
#include <glm/glm.hpp>

#include "engine/core/Path.h"

namespace gl3::ecs::components {
    struct PathFollow
    {
        Path* path = nullptr;
        int pathSegment = 0;

        glm::vec3 getTargetPosition() const
        {
            if (!path)
                return glm::vec3(0.0f);

            int pathSegmentCount = path->getPathSegmentCount();
            if (pathSegment >= pathSegmentCount)
                return path->getCellByPathSegmentIndex(pathSegmentCount - 1)->getWorldPositionCenter();

            return path->getCellByPathSegmentIndex(pathSegment)->getWorldPositionCenter();
        }

        void advanceIfReached(const glm::vec3& currentPosition)
        {
            if (!path || pathSegment >= path->getPathSegmentCount())
            {
                return;
            }
            glm::vec3 target = path->getCellByPathSegmentIndex(pathSegment)->getWorldPositionCenter();
            if (glm::distance(currentPosition, target) < 1.0f)
            {
                pathSegment++;
            }
        }

        void advance()
        {
            pathSegment++;
        }
    };
}
