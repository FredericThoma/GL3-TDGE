#pragma once

#include "engine/waves/WaveInfo.h"

namespace gl3::ecs::components
{
    struct SpawnRequest {
        std::string tag;
        SpawnInfo spawnInfo;
    };
}