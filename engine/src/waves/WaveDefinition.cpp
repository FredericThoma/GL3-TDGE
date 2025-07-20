#include "engine/waves/WaveDefinition.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace engine::waves;

EnemySpawnTemplate EnemySpawnTemplate::from_json(const json& j) {
    return EnemySpawnTemplate {
        .delay = j.value("delay", 0.0f),
        .type = j.at("type").get<std::string>(),
        .position = glm::vec2(j.at("position")[0], j.at("position")[1])
    };
}

WaveTemplate WaveTemplate::from_json(const json& j) {
    WaveTemplate wave;
    wave.wave_id = j.at("wave_id").get<int>();
    wave.start_time = j.value("start_time", 0.0f);
    for (const auto& spawn_json : j.at("spawns")) {
        wave.spawns.push_back(EnemySpawnTemplate::from_json(spawn_json));
    }
    return wave;
}

WaveTemplateSet WaveTemplateSet::from_json_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open wave definition file: " + file_path);
    }

    json j;
    file >> j;

    WaveTemplateSet set;
    for (const auto& wave_json : j.at("waves")) {
        set.waves.push_back(WaveTemplate::from_json(wave_json));
    }
    return set;
}
