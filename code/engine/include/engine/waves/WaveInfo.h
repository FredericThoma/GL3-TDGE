#pragma once
#include "glm/vec3.hpp"


struct SpawnInfo {
    float delay;
    std::string type;
    glm::vec3 position;
    float health = 100.0f;
    bool spawned = false;
};
    struct WaveInfo {
        int wave_id;
        float current_time = 0.0f;
        float duration = 10.0f;
        std::vector<SpawnInfo> spawns;
    };
