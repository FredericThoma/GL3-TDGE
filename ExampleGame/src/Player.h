#pragma once
#include "engine/Events.h"

class Player {
public:
    using event_t = typename gl3::engine::events::Event<Player>;
    event_t onPlayerDeath;

    void getDamage(int value) {
        health -= value;

        if(health <= 0) {
            onPlayerDeath.invoke();
        }
    }

private:
    int health = 100;
};

