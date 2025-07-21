#include <iostream>

#include "engine/Game.h"
#include "Player.h"
#include "engine/rendering/Texture.h"
#include "engine/rendering/Renderer.h"
#include "engine/ecs/Scene.h"
#include "engine/ecs/systems/RenderSystem.h"
#include "engine/ecs/components/Transform.h"
#include "engine/rendering/Assets.h"
#include "engine/ecs/components/Sprite.h"
#include "engine/core/Grid.h"
#include "engine/ecs/systems/MovementSystem.h"
#include "engine/ecs/systems/SpawnSystem.h"
#include "engine/ecs/systems/WaveSystem.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 1280;
constexpr int CELLSIZE = 64;



class MyGame : public gl3::engine::Game {
public:

    MyGame()
        : Game(1280, 1280, "My 2D Game"),
          scene(),
          renderSystem(renderer){}

    void start() override {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        entt::registry& registry = scene.getRegistry();

        int width, height;
        glfwGetWindowSize(getWindow(), &width, &height);
        glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), -2.0f, 2.0f);
        glm::mat4 view = glm::mat4(1.0f);
        renderSystem.SetView(view);
        renderSystem.SetProjection(projection);
        spawnSystem = std::make_unique<SpawnSystem>(registry);
        waveSystem = std::make_unique<WaveSystem>(registry);
        movementSystem = std::make_unique<MovementSystem>(registry);
        auto all_waves = waveSystem->allWavesFromJson(gl3::resolveAssetPath("wave_definition_test.json"));
        waveSystem->setWaves(all_waves);
        waveSystem->resetWaves();

        std::vector<glm::ivec2> pathData;
        for (int x = 0; x <= 18; ++x) {
            pathData.emplace_back(x, 1); // move right
        }
        for (int y = 1; y <= 19; ++y) {
            pathData.emplace_back(18, y); // move up
        }

        grid = Grid(WIDTH, HEIGHT, CELLSIZE);
        grid.SetPath(pathData);
        entt::entity entity = registry.create();
        registry.emplace<gl3::ecs::components::Transform>(
            entity,
            glm::vec3(500.0, 500.0f, 1.0f),
            0.0f,
            glm::vec2(100.0f, 100.0f)
        );



        glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};

        auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/turret_placeholder.png"));
        registry.emplace<gl3::ecs::components::Sprite>(entity, texture, color);


    }

    void update(GLFWwindow* window) override {
        std::cout << "update" << std::endl;
        waveSystem->update();
        spawnSystem->update();
        movementSystem->update();
    }

    void draw() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        entt::registry& registry = scene.getRegistry();
        renderSystem.renderGrid(grid);
        renderSystem.render(registry);

    }
private:

    gl3::renderer::Renderer renderer;
    Grid grid;
    gl3::ecs::Scene scene;
    gl3::ecs::systems::RenderSystem renderSystem;
    std::unique_ptr<WaveSystem> waveSystem;
    std::unique_ptr<SpawnSystem> spawnSystem;
    std::unique_ptr<MovementSystem> movementSystem;
};
