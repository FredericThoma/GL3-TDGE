#include "engine/ecs/systems/TargetingSystem.h"
#include "engine/ecs/Components.h"
#include <entt/entt.hpp>
#include <algorithm>


void TargetingSystem::update() {
    auto view = registry.view<gl3::ecs::components::Targeting>();

    for (auto entity : view) {
        auto& targeting = view.get<gl3::ecs::components::Targeting>(entity);
        entt::entity enemy = entt::null;
        switch (targeting.mode)
        {

        case gl3::ecs::components::TargetingMode::Nearest:
            enemy = getNearestEnemy(entity);
            if (enemy == entt::null)
            {
                break;
            }

            targeting.targetPosition = registry.get<gl3::ecs::components::Transform>(enemy).position;
            targeting.target = enemy;
            break;

        default:
            enemy = getNearestEnemy(entity);
            if (enemy == entt::null)
            {
                break;
            }
            targeting.targetPosition = registry.get<gl3::ecs::components::Transform>(enemy).position;
            targeting.target = enemy;
            break;
        }
    }
}
entt::entity TargetingSystem::getNearestEnemy(entt::entity entity) const
{

    auto& transform = registry.get<gl3::ecs::components::Transform>(entity);
    glm::vec3 position = transform.position;
    float bestDistance = (std::numeric_limits<float>::max)();
    entt::entity bestTarget = entt::null;
    auto view = registry.view<gl3::ecs::components::EnemyTag, gl3::ecs::components::Transform>();
    for (auto enemy : view) {
        auto& enemyTranform = view.get<gl3::ecs::components::Transform>(enemy);
        glm::vec3 enemyPosition = enemyTranform.position;
        float distance = glm::distance(enemyPosition, position);
        if (distance < bestDistance)
        {
            bestDistance = distance;
            bestTarget = enemy;
        }
    }
    return bestTarget;
}

entt::entity TargetingSystem::getLowestEnemy() const {
    // TODO: implement this
    return entt::null;
}

entt::entity TargetingSystem::getFurthestEnemy() const {
    // TODO: implement this
    return entt::null;
}
