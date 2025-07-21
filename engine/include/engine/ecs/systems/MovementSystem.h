#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include "engine/core/Grid.h"
#include "engine/ecs/components/Path.h"

class MovementSystem {
public:
    MovementSystem(Grid& grid);

    void update(entt::registry& registry, float deltaTime);

private:
    Grid& grid_;
};
