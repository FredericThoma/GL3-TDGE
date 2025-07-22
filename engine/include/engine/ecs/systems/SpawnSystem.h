#pragma once

#include "entt/entt.hpp"
#include <glm/glm.hpp>

class SpawnSystem {
public:
    explicit SpawnSystem(entt::registry& reg);

    void update();
    void spawnEnemy(glm::vec3 position, float health);

private:
    entt::registry& registry;
};
