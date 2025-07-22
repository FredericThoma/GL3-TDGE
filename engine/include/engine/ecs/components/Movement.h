#pragma once

#include <glm/vec3.hpp>


namespace gl3::ecs::components
{
    struct Movement {
        glm::vec3 velocity = glm::vec3(0.0f);
        glm::vec3 acceleration = glm::vec3(0.0f);
        float maxSpeed = 1000.0f;
        bool canMove = true;
        bool isMoving = false;
    } ;
}