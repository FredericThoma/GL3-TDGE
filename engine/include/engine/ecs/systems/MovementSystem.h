#pragma once

#include "entt/entt.hpp"

class MovementSystem {
public:
    explicit MovementSystem(entt::registry& reg);

    void update();
    void moveEntity(entt::entity entity);
    void moveEntityAlongPath(entt::entity entity);

private:
    static bool checkCanMove(entt::entity entity);

    entt::registry& registry;
};
