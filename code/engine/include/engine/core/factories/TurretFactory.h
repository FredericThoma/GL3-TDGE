#pragma once
#include <entt/entt.hpp>
#include "engine/ecs/Components.h"


    class TurretFactory {
    public:
        TurretFactory();
        static entt::entity create(entt::registry& registry, const gl3::ecs::components::Transform& transform, const gl3::ecs::components::Movement& movement, const gl3::ecs::components::Sprite& sprite);
    };


