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
#include "engine/ecs/systems/ShootingSystem.h"
#include "engine/ecs/systems/SpawnSystem.h"
#include "engine/ecs/systems/TargetingSystem.h"
#include "engine/ecs/systems/WaveSystem.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#include "EnemyProjectileCollision.h"
#include "engine/core/InputManager.h"
#include "engine/ecs/components/AudioClip.h"
#include "engine/ecs/components/Projectile.h"
#include "engine/ecs/systems/AudioSystem.h"
#include "engine/ecs/systems/CollisionSystem.h"
#include "engine/ecs/systems/DestructionSystem.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 1280;
constexpr int CELLSIZE = 64;



class MyGame : public gl3::engine::Game {
public:

    MyGame()
        : Game(1280, 1280, "My 2D Game"),
          scene(),
          renderSystem(renderer),
    grid(WIDTH, HEIGHT, CELLSIZE){}

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
        renderSystem.start();
        renderer.setWindow(getWindow());

        InputManager::RegisterCallbacks(getWindow(), &inputManager);

        auto uiib = std::make_shared<UIImageButton>();
        uiib->id = "1";
        uiib->texture=gl3::Texture(gl3::resolveAssetPath("textures/TurmB.png"), false);
        uiib->onClick = [uiib]() mutable {
            uiib->selected = !uiib->selected;
            uiib->bg_col = uiib->selected ? uiib->bg_col_sel : uiib->bg_col_unsel;
        };

        auto uiib2 = std::make_shared<UIImageButton>();
        uiib2->id = "2";
        uiib2->texture=gl3::Texture(gl3::resolveAssetPath("textures/Turret.png"), false);
        uiib2->onClick = [uiib2]() mutable {
            uiib2->selected = !uiib2->selected;
            uiib2->bg_col = uiib2->selected ? uiib2->bg_col_sel : uiib2->bg_col_unsel;
        };

        std::vector<UIElement> elements;
        auto uie = UIElement();
        uie.imageButtons.push_back(uiib);
        uie.imageButtons.push_back(uiib2);

        auto uii2 = UIImage();

        uii2.texture = gl3::Texture(gl3::resolveAssetPath("textures/TurmB.png"), false);
        //uie.images.push_back(std::move(uii2));

        uie.title = "test";
        elements.push_back(std::move(uie));

        collisionSystem = std::make_unique<gl3::ecs::systems::CollisionSystem>();
        collisionSystem->setCallback([&registry](entt::entity a, entt::entity b) {
            handleEnemyProjectileCollosion(registry, a, b);
        });


        spawnSystem = std::make_unique<SpawnSystem>(registry);
        waveSystem = std::make_unique<WaveSystem>(registry);
        movementSystem = std::make_unique<MovementSystem>(registry);
        targetingSystem = std::make_unique<TargetingSystem>(registry);
        audioSystem = std::make_unique<AudioSystem>(registry);
        shootingSystem = std::make_unique<ShootingSystem>(registry);
        destructionSystem = std::make_unique<DestructionSystem>(registry);
        auto all_waves = waveSystem->allWavesFromJson(gl3::resolveAssetPath("wave_definition_test.json"));
        waveSystem->setWaves(all_waves);
        waveSystem->resetWaves();


        auto waveProgressDisplay = UIElement();
        UIText waveProgressText;
        waveProgressText.text = std::to_string(waveSystem->getCurrentWaveIndex()) + " / " +
                                std::to_string(waveSystem->getNumberWavesTotal());

        waveProgressDisplay.title = "Wave Progress";
        waveProgressDisplay.texts.push_back(std::move(waveProgressText));

        elements.push_back(std::move(waveProgressDisplay));

        userInterface = std::make_unique<UserInterface>(std::move(elements));



        std::vector<glm::vec2> PathCellIndices;
        for (int x = 0; x <= 18; ++x) {
            PathCellIndices.emplace_back(glm::vec2(x, 1.0f));
        }
        for (int y = 1; y <= 19; ++y) {
            PathCellIndices.emplace_back(glm::vec2(18, y));
        }

        grid.MarkPathCells(PathCellIndices);

        entt::entity pathEntity = registry.create();
        path = std::make_shared<Path>(PathCellIndices, grid);
        registry.emplace<std::shared_ptr<Path>>(pathEntity, path);

        entt::entity entity = registry.create();
        registry.emplace<gl3::ecs::components::Transform>(
            entity,
            glm::vec3(500.0, 500.0f, 1.0f),
            0.0f,
            glm::vec2(300.0f, 300.0f)
        );
        registry.emplace<gl3::ecs::components::Targeting>(entity);
        registry.emplace<gl3::ecs::components::Shooting>(entity, 10.0f, 1000, 1.0f);
        registry.emplace<gl3::ecs::components::AudioClip>(
    entity,
    "audio/electronic-wave.mp3"
);
        registry.get<gl3::ecs::components::AudioClip>(entity).PlayLooping();
        glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};
        auto tex = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/TurmB.png"));
        registry.emplace<gl3::ecs::components::Sprite>(entity, tex, glm::vec4(1.0f));



    }

    void update(GLFWwindow* window) override {
        destructionSystem->update();
        inputManager.Update();
        handleInputs(window);
        waveSystem->update();
        spawnSystem->update();
        movementSystem->update();
        targetingSystem->update();
        shootingSystem->update();
        audioSystem->update();
        collisionSystem->update(scene.getRegistry());
    }

    void handleInputs(GLFWwindow* window)
    {
        if (inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        if (inputManager.IsKeyPressed(GLFW_KEY_H)) {
            std::cout << "H" << std::endl;
        }
    }


    void draw() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        entt::registry& registry = scene.getRegistry();
        renderSystem.renderGrid(grid);
        renderSystem.render(registry);
        renderer.drawUI(*userInterface);

    }
private:

    gl3::renderer::Renderer renderer;
    Grid grid;
    gl3::ecs::Scene scene;
    gl3::ecs::systems::RenderSystem renderSystem;
    std::unique_ptr<WaveSystem> waveSystem;
    std::unique_ptr<SpawnSystem> spawnSystem;
    std::unique_ptr<MovementSystem> movementSystem;
    std::unique_ptr<ShootingSystem> shootingSystem;
    std::unique_ptr<AudioSystem> audioSystem;
    std::unique_ptr<TargetingSystem> targetingSystem;
    std::unique_ptr<UserInterface> userInterface;

    std::unique_ptr<DestructionSystem> destructionSystem;
    std::unique_ptr<gl3::ecs::systems::CollisionSystem> collisionSystem;
    std::shared_ptr<Path> path;
    InputManager inputManager;
};
