#pragma once

#include "entt/entt.hpp"
#include "soloud.h"

class AudioSystem {
public:
    explicit AudioSystem(entt::registry& registry);

    void update();


private:
    SoLoud::Soloud audio;
    entt::registry& registry;
};
