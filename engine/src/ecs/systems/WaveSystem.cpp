#include "engine/ecs/systems/WaveSystem.h"

#include <iostream>

#include "engine/ecs/components/SpawnRequest.h"
#include "engine/ecs/components/Tags.h"

constexpr float DELTATIME = 1 / 60.0f;


WaveSystem::~WaveSystem()
    {

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
    if (currentWave->current_time >= currentWave->duration)
    {
        nextWave();
    }
    for (auto& spawnInfo : currentWave->spawns)
    {
        if (!spawnInfo.spawned && currentWave->current_time >= spawnInfo.delay){
            spawnInfo.spawned = true;
            auto spawn_entity = registry.create();
            std::string tag = "enemy";
            registry.emplace<gl3::ecs::components::EnemyTag>(spawn_entity);
            registry.emplace<gl3::ecs::components::SpawnRequest>(spawn_entity, gl3::ecs::components::SpawnRequest{tag, spawnInfo});
        }
    }

    currentWave->current_time += DELTATIME;

}

std::vector<WaveInfo> WaveSystem::allWavesFromJson(const std::filesystem::path& file_path)
    {
        return engine::waves::WaveParser::from_json_file(file_path);
    }

