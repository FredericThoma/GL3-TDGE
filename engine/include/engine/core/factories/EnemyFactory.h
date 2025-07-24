#pragma once
#include <entt/entt.hpp>
#include "engine/ecs/Components.h"


    class EnemyFactory {
    public:
        EnemyFactory();
        static entt::entity createEnemy(entt::registry& registry, const gl3::ecs::components::Transform& transform, const gl3::ecs::components::Movement& movement, const gl3::ecs::components::Sprite& sprite, float maxHealth);
    };


