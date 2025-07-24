#include "engine/waves/WaveParser.h"
#include "engine/waves/WaveInfo.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "glm/vec3.hpp"

using json = nlohmann::json;


std::vector<WaveInfo> engine::waves::WaveParser::from_json_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path.string());
    }

    json j;
    file >> j;

    std::vector<WaveInfo> waves;

    const auto& wave_array = j.at("waves");
    for (const auto& wave_json : wave_array) {
        WaveInfo wave;
        wave.wave_id = wave_json.at("wave_id").get<int>();
        wave.duration = wave_json.at("duration").get<float>();

        for (const auto& spawn_json : wave_json.at("spawns")) {
            SpawnInfo spawn;
            spawn.delay = spawn_json.at("delay").get<float>();
            spawn.type = spawn_json.at("type").get<std::string>();
            auto pos_array = spawn_json.at("position");
            spawn.position = glm::vec3(pos_array[0], pos_array[1], pos_array[2]);
            wave.spawns.push_back(spawn);
        }

        waves.push_back(wave);
    }

    return waves;
}