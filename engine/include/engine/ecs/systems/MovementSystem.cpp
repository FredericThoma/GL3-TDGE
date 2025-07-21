#include "MovementSystem.h"

#include <iostream>

#include "engine/Events.h"
#include "engine/ecs/Components.h"
#include "entt/entt.hpp"

#include "engine/rendering/Assets.h"
#include "glm/gtx/string_cast.hpp"

using namespace gl3::ecs::components;

MovementSystem::MovementSystem(entt::registry& reg) : registry(reg) {}

void MovementSystem::update() {
    auto pathView = registry.view<Movement, Transform, PathFollow>();
    pathView.each([this](auto entity, auto&, auto&, auto&) {
        moveEntityAlongPath(entity);
    });

    auto view = registry.view<Movement, Transform>(entt::exclude<PathFollow>);
    view.each([this](auto entity, auto&, auto&) {
        moveEntity(entity);
    });
}



void MovementSystem::moveEntity(entt::entity entity)
{
    auto& movement = registry.get<Movement>(entity);
    auto& transform = registry.get<Transform>(entity);

    movement.canMove = checkCanMove(entity);

    if (!movement.canMove) {
        movement.isMoving = false;
        return;
    }

    movement.velocity += movement.acceleration;
    transform.position += movement.velocity;
    movement.isMoving = glm::length(movement.velocity) > 0.001f;

}

void MovementSystem::moveEntityAlongPath(entt::entity entity)
{
    std::cout<<"moveEntityAlongPath"<<std::endl;
    auto& movement = registry.get<Movement>(entity);
    auto& transform = registry.get<Transform>(entity);
    auto& pathFollow = registry.get<PathFollow>(entity);

    if (!movement.canMove)
        return;

    glm::vec3 targetPosition = pathFollow.getTargetPosition(transform.position);
    glm::vec3 direction = targetPosition - transform.position;
    float distance = glm::length(direction);

    const float epsilon = 0.01f;
    if (distance < epsilon) {
        movement.isMoving = false;
        movement.velocity = glm::vec3(0.0f);
        return; // Already at or very close to target
    }

    direction = glm::normalize(direction);

    // Apply acceleration toward target
    movement.acceleration = direction * movement.maxSpeed;

    // Update velocity
    movement.velocity += movement.acceleration; // You may want to scale this by deltaTime in a real update loop

    // Clamp velocity to max speed
    if (glm::length(movement.velocity) > movement.maxSpeed) {
        movement.velocity = glm::normalize(movement.velocity) * movement.maxSpeed;
    }

    // Move the entity
    transform.position += movement.velocity; // Again, scale by deltaTime in practice

    movement.isMoving = true;
}



bool MovementSystem::checkCanMove(entt::entity entity) {
    // potential for expansion
    return true;
}
