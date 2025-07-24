#include "engine/ecs/systems/ShootingSystem.h"
#include "engine/ecs/Components.h"
#include <entt/entt.hpp>
#include <algorithm>

#include "engine/ecs/components/Projectile.h"

// TODO: REFACTOR DT
constexpr float DELTATIME = 1 / 60.0f;

ShootingSystem::~ShootingSystem() = default;

void ShootingSystem::update() {
    auto view = registry.view<gl3::ecs::components::Shooting, gl3::ecs::components::Targeting, gl3::ecs::components::Transform>();
    for (auto entity : view) {
        auto& shooting = view.get<gl3::ecs::components::Shooting>(entity);
        auto& targeting = view.get<gl3::ecs::components::Targeting>(entity);
        auto& transform = view.get<gl3::ecs::components::Transform>(entity);

        if (shooting.countdownUntilNextShot > 0.0f) {
            shooting.countdownUntilNextShot -= DELTATIME;
            continue;
        }

        if (shooting.countdownUntilNextShot <= 0.0f) {
            auto bulletSpawnRequest = registry.create();
            registry.emplace<gl3::ecs::components::BulletTag>(bulletSpawnRequest);
            gl3::ecs::components::Projectile projectile = gl3::ecs::components::Projectile();
            projectile.damage = shooting.damage;
            projectile.startPosition = transform.position;
            projectile.target = targeting.target;
            projectile.targetPosition = targeting.targetPosition;
            projectile.bulletSpeed = shooting.bulletSpeed;
            registry.emplace<gl3::ecs::components::Projectile>(bulletSpawnRequest, projectile);
            registry.emplace<gl3::ecs::components::SpawnRequest>(bulletSpawnRequest);
            shooting.countdownUntilNextShot = shooting.cooldown;
        }
    }
}


