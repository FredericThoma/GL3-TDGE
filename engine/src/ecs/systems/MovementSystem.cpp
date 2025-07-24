#include "engine/ecs/systems/MovementSystem.h"

#include <iostream>

#include "engine/Events.h"
#include "engine/ecs/Components.h"
#include "entt/entt.hpp"

#include "engine/rendering/Assets.h"
#include "glm/gtx/string_cast.hpp"


MovementSystem::MovementSystem(entt::registry& reg) : registry(reg) {}

void MovementSystem::update() {
    auto pathView = registry.view<gl3::ecs::components::Movement, gl3::ecs::components::Transform, gl3::ecs::components::PathFollow>();
    pathView.each([this](auto entity, auto&, auto&, auto&) {
        moveEntityAlongPath(entity);
    });

    auto view = registry.view<gl3::ecs::components::Movement, gl3::ecs::components::Transform>(entt::exclude<gl3::ecs::components::PathFollow>);
    view.each([this](auto entity, auto&, auto&) {
        moveEntity(entity);
    });
}



void MovementSystem::moveEntity(entt::entity entity)
{
    auto& movement = registry.get<gl3::ecs::components::Movement>(entity);
    auto& transform = registry.get<gl3::ecs::components::Transform>(entity);

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
    //TODO! Make Deltatime set- & get-able globally

    const float deltaTime = 1 / 60.0f;
    auto& movement = registry.get<gl3::ecs::components::Movement>(entity);
    auto& transform = registry.get<gl3::ecs::components::Transform>(entity);
    auto& pathFollow = registry.get<gl3::ecs::components::PathFollow>(entity);

    if (!movement.canMove)
        return;

    pathFollow.advanceIfReached(transform.position);
    glm::vec3 targetPosition = pathFollow.getTargetPosition();

    glm::vec3 direction = targetPosition - transform.position;
    float distance = glm::length(direction);
    float moveStep = movement.maxSpeed * deltaTime;

    if (distance < moveStep)
    {
        pathFollow.advance();
        targetPosition = pathFollow.getTargetPosition();
        direction = targetPosition - transform.position;
        distance = glm::length(direction);
    }

    if (distance > 0.0001f)
        direction = glm::normalize(direction);
    else
        direction = glm::vec3(0.0f);

    direction.z = 0.0f;

    movement.velocity = direction * movement.maxSpeed;


    transform.position += movement.velocity * deltaTime;

    movement.acceleration = glm::vec3(0.0f);
    movement.isMoving = true;
}




bool MovementSystem::checkCanMove(entt::entity entity) {
    // potential for expansion
    return true;
}
