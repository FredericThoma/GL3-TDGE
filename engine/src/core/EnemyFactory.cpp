#include "engine/core/EnemyFactory.h"

#include <iostream>
#include "engine/ecs/Components.h"

namespace gl3::ecs::components
{
    EnemyFactory::EnemyFactory() {
    }

    entt::entity EnemyFactory::createEnemy(entt::registry& registry, const Transform& transform, const Movement& movement, const Sprite& sprite, float maxHealth)
    {
        std::cout << "creating enemy" << std::endl;
        entt::entity enemy = registry.create();
        registry.emplace<Transform>(enemy, transform);
        registry.emplace<Sprite>(enemy, sprite);
        registry.emplace<Health>(enemy, Health{maxHealth});
        registry.emplace<PathFollow>(enemy, PathFollow{});
        registry.emplace<EnemyTag>(enemy);
        registry.emplace<Movement>(enemy, movement);
        return enemy;
    }

}