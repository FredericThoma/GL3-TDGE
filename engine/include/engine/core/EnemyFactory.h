#pragma once
#include <entt/entt.hpp>
#include "engine/ecs/Components.h"

namespace gl3::ecs::components
{
    class EnemyFactory {
    public:
        EnemyFactory();
        static entt::entity createEnemy(entt::registry& registry, const Transform& transform, const Movement& movement, const Sprite& sprite, float maxHealth);
    };
}

