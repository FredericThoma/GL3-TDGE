#include "engine/ecs/systems/SpawnSystem.h"
#include "../../../include/engine/core/factories/EnemyFactory.h"
#include "engine/ecs/Components.h"
#include "engine/rendering/Assets.h"
#include <iostream>
#include <memory>


SpawnSystem::SpawnSystem(entt::registry& reg) : registry(reg) {}

void SpawnSystem::update() {

    auto view = registry.view<gl3::ecs::components::SpawnRequest>();
    for (auto entity : view) {
        auto& request = view.get<gl3::ecs::components::SpawnRequest>(entity);
        const auto& spawnInfo = request.spawnInfo;
        spawnEnemy(spawnInfo.position, spawnInfo.health);
        registry.destroy(entity);
    }
}

void SpawnSystem::spawnEnemy(glm::vec3 position, float health) {
    auto transform = std::make_unique<gl3::ecs::components::Transform>(position, 0.0f, glm::vec2(100.0f, 100.0f));
    auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/enemy.png"));
    auto sprite = std::make_unique<gl3::ecs::components::Sprite>(texture, glm::vec4(1.0f));
    auto movement = std::make_unique<gl3::ecs::components::Movement>();
    movement->velocity = glm::vec3(1.0f, 1.0f, 0.0f);
    movement->acceleration = glm::vec3(0.01f, 0.0f, 0.0f);
    EnemyFactory::createEnemy(registry, *transform, *movement, *sprite, health);
}
