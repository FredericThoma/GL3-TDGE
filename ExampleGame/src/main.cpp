#include "MyGame.h"
#include <iostream>
#include <exception>  // for std::exception
#include "engine/waves/WaveDefinition.h"
#include "engine/rendering/Assets.h"

static void test_json() {
    try {
        engine::waves::WaveTemplateSet waveSet = engine::waves::WaveTemplateSet::from_json_file(gl3::resolveAssetPath("wave_definition_test.json"));

        for (const auto& wave : waveSet.waves) {
            std::cout << "Wave ID: " << wave.wave_id << ", Start Time: " << wave.start_time << "\n";
            for (const auto& spawn : wave.spawns) {
                std::cout << "  - Spawn: Type=" << spawn.type
                          << ", Delay=" << spawn.delay
                          << ", Position=(" << spawn.position.x << ", " << spawn.position.y << ")\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error loading wave data: " << e.what() << "\n";
    }
}

int main() {
    MyGame game;
    game.run();
    // test_json();
    return 0;
}
