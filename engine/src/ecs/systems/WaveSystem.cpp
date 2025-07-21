#include "engine/ecs/systems/WaveSystem.h"

#include <iostream>

#include "engine/ecs/components/SpawnRequest.h"


WaveSystem::~WaveSystem()
    {
        std::cout << "WaveSystem: Destructor called." << std::endl;
        // Clean up any dynamically allocated resources if you had them.
        // Since m_loadedWaveTemplateSets is a std::vector, it will
        // automatically clean up its contents.
    }

void WaveSystem::setWaves(const std::vector<WaveInfo>& waves) {
    allWaves = std::move(waves);
}

void WaveSystem::setWaves(std::vector<WaveInfo>&& waves) {
    allWaves = std::move(waves);
}
void WaveSystem::resetWaves()
{
    if (!allWaves.empty())
    {
        currentWave = &allWaves[0];
        waveTimer = 0.0f;
    }
}

void WaveSystem::nextWave()
{
    if (!currentWave)
        return;

    int current_id = currentWave->wave_id;

    if (current_id + 1 < static_cast<int>(allWaves.size()))
    {
        currentWave = &allWaves[current_id + 1];
        waveTimer = 0.0f;
    }
    else
    {
        std::cout << "VICTORY" << std::endl;

    }
}


void WaveSystem::update()
{
    for (auto& spawnInfo : currentWave->spawns)
    {
        if (!spawnInfo.spawned && waveTimer >= spawnInfo.delay){
            spawnInfo.spawned = true;
            auto spawn_entity = registry.create();
            std::string tag = "enemy";
            registry.emplace<SpawnRequest>(spawn_entity, SpawnRequest{tag, spawnInfo});
        }
    }
}

std::vector<WaveInfo> WaveSystem::allWavesFromJson(const std::filesystem::path& file_path)
    {
        return engine::waves::WaveParser::from_json_file(file_path);
    }

