#pragma once

#include "engine/waves/WaveParser.h"
#include "engine/waves/WaveInfo.h"
#include <vector>
#include <filesystem>
#include <chrono>


#include "entt/entt.hpp"

class WaveSystem {
public:
    explicit WaveSystem(entt::registry& registry) : registry(registry) {};
    ~WaveSystem();
    void setWaves(const std::vector<WaveInfo>& waves);
    void setWaves(std::vector<WaveInfo>&& waves);
    void resetWaves();
    static std::vector<WaveInfo> allWavesFromJson(const std::filesystem::path& file_path);

    void nextWave();
    void update();

private:
    std::vector<WaveInfo> allWaves;
    entt::registry& registry;
    float waveTimer = 0.0f;
    WaveInfo* currentWave = nullptr;
};
