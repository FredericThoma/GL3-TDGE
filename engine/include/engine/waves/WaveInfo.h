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
    float start_time;
    std::vector<SpawnInfo> spawns;
};