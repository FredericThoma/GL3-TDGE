#pragma once
#include <entt/entt.hpp>
#include "engine/ecs/Components.h"
#include "engine/ecs/components/Projectile.h"


class BulletFactory {
    public:
        BulletFactory();
        static entt::entity BulletFactory::create(entt::registry& registry,
                                                  const gl3::ecs::components::Transform& transform,
                                                  const gl3::ecs::components::Movement& movement,
                                                  const gl3::ecs::components::Sprite& sprite);
    };


