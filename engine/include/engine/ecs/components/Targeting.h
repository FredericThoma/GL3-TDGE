#pragma once
#include "entt/entt.hpp"

namespace gl3::ecs::components
{

    enum class TargetingMode {
        Nearest,
        LowestHealth,
        FurthestAdvanced,
    };

    struct Targeting {
        TargetingMode mode = TargetingMode::Nearest;
        entt::entity target = entt::null;
        glm::vec3 targetPosition = glm::vec3(0.0f);
    };
}
