#pragma once

#include "entt/entt.hpp"
#include <glm/glm.hpp>

class SpawnSystem {
public:
    explicit SpawnSystem(entt::registry& reg);

    void update();
    void spawnBullet(entt::entity bulletSpawnRequest);
    void spawnEnemy(entt::entity enemySpawnRequest);

private:
    entt::registry& registry;
};
