#include "engine/ecs/systems/SpawnSystem.h"
#include "../../../include/engine/core/factories/EnemyFactory.h"
#include "engine/ecs/Components.h"
#include "engine/rendering/Assets.h"
#include <iostream>
#include <memory>

#include "engine/core/factories/BulletFactory.h"
#include "engine/ecs/components/Projectile.h"


SpawnSystem::SpawnSystem(entt::registry& reg) : registry(reg) {}


void SpawnSystem::update() {
    auto view = registry.view<gl3::ecs::components::SpawnRequest>();

    for (auto entity : view) {
        const auto& request = view.get<gl3::ecs::components::SpawnRequest>(entity);
        if (registry.any_of<gl3::ecs::components::BulletTag>(entity)) {
            spawnBullet(entity);
        } else if (registry.any_of<gl3::ecs::components::EnemyTag>(entity)) {
            spawnEnemy(entity);
        }

        registry.destroy(entity);
    }
}

void SpawnSystem::spawnBullet(entt::entity bulletSpawnRequest)
{
    auto projectile = registry.get<gl3::ecs::components::Projectile>(bulletSpawnRequest);
    auto transform = std::make_unique<gl3::ecs::components::Transform>(projectile.startPosition, 0.0f, glm::vec2(100.0f, 100.0f));
    auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/IceBallSmall.png"));
    auto sprite = std::make_unique<gl3::ecs::components::Sprite>(texture, glm::vec4(1.0f));
    auto movement = std::make_unique<gl3::ecs::components::Movement>();
    auto direction = glm::normalize(projectile.targetPosition - projectile.startPosition);
    movement->velocity = direction * projectile.bulletSpeed;
    BulletFactory::create(registry, *transform, *movement, *sprite);
}


void SpawnSystem::spawnEnemy(entt::entity enemySpawnRequest) {
    auto& spawnInfo = registry.get<gl3::ecs::components::SpawnRequest>(enemySpawnRequest).spawnInfo;
    auto position = spawnInfo.position;

    auto health = spawnInfo.health;
    auto transform = std::make_unique<gl3::ecs::components::Transform>(position, 0.0f, glm::vec2(100.0f, 100.0f));
    auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/Ghost.png"));
    auto sprite = std::make_unique<gl3::ecs::components::Sprite>(texture, glm::vec4(1.0f));
    auto movement = std::make_unique<gl3::ecs::components::Movement>();
    movement->velocity = glm::vec3(1.0f, 1.0f, 0.0f);
    movement->acceleration = glm::vec3(0.01f, 0.0f, 0.0f);
    EnemyFactory::createEnemy(registry, *transform, *movement, *sprite, health);
}
