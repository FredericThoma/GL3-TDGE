#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "engine/ecs/Components.h"
#include "engine/ecs/components/DestroyRequest.h"
#include "engine/ecs/components/Projectile.h"
#include "entt/entt.hpp"

void handleEnemyProjectileCollosion(entt::registry& registry, entt::entity entityA, entt::entity entityB)
{
    std::cout<<"ENEMY PROJ COLLSION"<<std::endl;
    entt::entity enemy = entt::null;
    entt::entity bullet = entt::null;

    if (registry.any_of<gl3::ecs::components::EnemyTag>(entityA) && registry.any_of<gl3::ecs::components::BulletTag>(entityB)) {
        enemy = entityA;
        bullet = entityB;
    } else if (registry.any_of<gl3::ecs::components::EnemyTag>(entityB) && registry.any_of<gl3::ecs::components::BulletTag>(entityA)) {
        enemy = entityB;
        bullet = entityA;
    } else {
        return;
    }
    if (!registry.all_of<gl3::ecs::components::Health>(enemy) || !registry.all_of<gl3::ecs::components::Projectile>(bullet)) {
        return;
    }

    auto& health = registry.get<gl3::ecs::components::Health>(enemy);
    auto& projectile = registry.get<gl3::ecs::components::Projectile>(bullet);
    std::cout << health.health << std::endl;
    if (registry.all_of<gl3::ecs::components::Projectile>(bullet)) {
        auto& projectile = registry.get<gl3::ecs::components::Projectile>(bullet);
        projectile.damage = 34;
    }
    health.health -= projectile.damage;
    if (health.health <= 0.0f)
    {
        registry.emplace<gl3::ecs::components::DestroyRequest>(enemy);
    }
    registry.emplace<gl3::ecs::components::DestroyRequest>(bullet);
}
