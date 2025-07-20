#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "nlohmann/json.hpp"

namespace engine::waves {

    struct EnemySpawnTemplate {
        float delay = 0.0f;
        std::string type;
        glm::vec2 position;

        static EnemySpawnTemplate from_json(const nlohmann::json& j);
    };

    struct WaveTemplate {
        int wave_id = -1;
        float start_time = 0.0f;
        std::vector<EnemySpawnTemplate> spawns;

        static WaveTemplate from_json(const nlohmann::json& j);
    };

    struct WaveTemplateSet {
        std::vector<WaveTemplate> waves;

        static WaveTemplateSet from_json_file(const std::string& file_path);
    };

}
