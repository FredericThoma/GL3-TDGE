#pragma once
#include "entt/entt.hpp"
#include "glm/vec3.hpp"

namespace gl3::ecs::components
{
    struct Projectile {
        float damage;
        float bulletSpeed;
        bool hit=false;
        entt::entity target;
        glm::vec3 targetPosition;
        glm::vec3 startPosition;
    };

}
