#include "engine/core/factories/TurretFactory.h"

TurretFactory::TurretFactory() {
}

entt::entity TurretFactory::create(entt::registry& registry,
                                   const gl3::ecs::components::Transform& transform,
                                   const gl3::ecs::components::Movement& movement,
                                   const gl3::ecs::components::Sprite& sprite) {
    entt::entity entity = registry.create();

    registry.emplace<gl3::ecs::components::Transform>(entity, transform);
    registry.emplace<gl3::ecs::components::Movement>(entity, movement);
    registry.emplace<gl3::ecs::components::Sprite>(entity, sprite);
    registry.emplace<gl3::ecs::components::TurretTag>(entity);


    return entity;
}
