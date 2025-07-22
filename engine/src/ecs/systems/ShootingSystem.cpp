#include "engine/ecs/systems/ShootingSystem.h"
#include "engine/ecs/Components.h"
#include <entt/entt.hpp>
#include <algorithm>

// TODO: REFACTOR DT
constexpr float DELTATIME = 1 / 60.0f;

ShootingSystem::~ShootingSystem() = default;

void ShootingSystem::update() {
    auto view = registry.view<gl3::ecs::components::Shooting, gl3::ecs::components::Targeting>();

    for (auto entity : view) {
        auto& shooting = view.get<gl3::ecs::components::Shooting>(entity);
        auto& targeting = view.get<gl3::ecs::components::Targeting>(entity);

        if (shooting.countdownUntilNextShot > 0.0f) {
            shooting.countdownUntilNextShot = std::max(0.0f, shooting.countdownUntilNextShot - DELTATIME);
            continue;
        }

        if (shooting.countdownUntilNextShot == 0.0f) {
            auto targetPosition = targeting.targetPosition;
            shooting.countdownUntilNextShot = shooting.cooldown;
        }
    }
}


