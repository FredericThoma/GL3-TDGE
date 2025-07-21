#include "engine/core/EnemyFactory.h"
#include "engine/ecs/Components.h"
#include "entt/entt.hpp"
#include <memory>
#include "engine/waves/WaveInfo.h"
#include "engine/rendering/Assets.h"


class SpawnSystem {
public:
    SpawnSystem(entt::registry& reg) : registry(reg) {}

    void update() {
        std::cout << "SpawnSystem update" << std::endl;

        auto view = registry.view<SpawnRequest>();
        for (auto entity : view) {
            std::cout << "SpawnSystem TRY" << std::endl;
            auto& request = view.get<SpawnRequest>(entity);
            const auto& spawnInfo = request.spawnInfo;
            spawnEnemy(spawnInfo.position, spawnInfo.health);
            registry.destroy(entity);
        }
    }

    void spawnEnemy(glm::vec3 position, float health)
    {
        auto transform = std::make_unique<gl3::ecs::components::Transform>(position, 0.0f,glm::vec2(100.0f, 100.0f) );
        auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/enemy.png"));
        auto sprite = std::make_unique<gl3::ecs::components::Sprite>(texture, glm::vec4(1.0f));
        auto movement = std::make_unique<Movement>();
        movement->velocity = glm::vec3(1.0f, 1.0f, 0.0f);
        movement->acceleration = glm::vec3(0.01f, 0.0f, 0.0f);
        gl3::ecs::components::EnemyFactory::createEnemy(registry, *transform, *movement, *sprite, health);
    }

private:
    entt::registry& registry;
};
