#include "engine/core/factories/BulletFactory.h"

#include "engine/ecs/components/Collider.h"
#include "engine/ecs/components/Projectile.h"

BulletFactory::BulletFactory() {
}

entt::entity BulletFactory::create(entt::registry& registry,
                                   const gl3::ecs::components::Transform& transform,
                                   const gl3::ecs::components::Movement& movement,
                                   const gl3::ecs::components::Sprite& sprite
                                  ) {
    entt::entity entity = registry.create();

    registry.emplace<gl3::ecs::components::Transform>(entity, transform);
    registry.emplace<gl3::ecs::components::Movement>(entity, movement);
    registry.emplace<gl3::ecs::components::Sprite>(entity, sprite);
    registry.emplace<gl3::ecs::components::BulletTag>(entity);
    registry.emplace<gl3::ecs::components::CircleCollider>(entity, 50.0f);
    registry.emplace<gl3::ecs::components::Projectile>(entity);

    return entity;
}
