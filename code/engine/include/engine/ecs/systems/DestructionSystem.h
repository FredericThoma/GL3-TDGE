#pragma once

#include "entt/entt.hpp"
#include <glm/glm.hpp>

#include "engine/ecs/components/DestroyRequest.h"

class DestructionSystem {
public:
    explicit DestructionSystem(entt::registry& reg)
        : registry(reg) {}

    void update()
    {
        auto view = registry.view<gl3::ecs::components::DestroyRequest>();

        for (auto entity : view) {
            registry.destroy(entity);

        }
    }

private:
    entt::registry& registry;
};
