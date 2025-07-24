#include "../../../include/engine/core/factories/EnemyFactory.h"

#include <iostream>
#include "engine/ecs/Components.h"
#include "engine/ecs/components/Collider.h"


EnemyFactory::EnemyFactory() {
    }

    entt::entity EnemyFactory::createEnemy(entt::registry& registry, const gl3::ecs::components::Transform& transform, const gl3::ecs::components::Movement& movement, const gl3::ecs::components::Sprite& sprite, float maxHealth)
    {
        std::shared_ptr<Path> foundPath = nullptr;
        auto view = registry.view<std::shared_ptr<Path>>();
        for (auto entity : view) {
            foundPath = view.get<std::shared_ptr<Path>>(entity);
        }

        if (foundPath) {
            Path* pathPtr = foundPath.get();
        }

        entt::entity enemy = registry.create();
        registry.emplace<gl3::ecs::components::Transform>(enemy, transform);
        registry.emplace<gl3::ecs::components::Sprite>(enemy, sprite);
        registry.emplace<gl3::ecs::components::Health>(enemy, gl3::ecs::components::Health{maxHealth});
        registry.emplace<gl3::ecs::components::PathFollow>(enemy, gl3::ecs::components::PathFollow{foundPath.get()});
        registry.emplace<gl3::ecs::components::EnemyTag>(enemy);
        registry.emplace<gl3::ecs::components::Movement>(enemy, movement);
        registry.emplace<gl3::ecs::components::CircleCollider>(enemy, 50.0f);
        return enemy;
    }

