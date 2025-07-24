#include <iostream>

#include "engine/Game.h"
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
#include "Shop.h"
#include "engine/core/InputManager.h"
#include "engine/ecs/systems/AudioSystem.h"
#include "engine/ecs/systems/CollisionSystem.h"
#include "engine/ecs/systems/DestructionSystem.h"

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1280;
constexpr int CELLSIZE = 64;



class MyGame : public gl3::engine::Game {
public:

    MyGame()
        : Game(1920, 1280, "My 2D Game"),
          scene(),
          renderSystem(renderer),
    registry(),
    grid(WIDTH, HEIGHT, CELLSIZE){}

    void start() override {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shop = Shop();
        auto shopTurret = std::make_shared<ShopTurret>("turret1", 8, 500, 1.5f, "textures/TurretIce.png");
        shop.addTurret(shopTurret);
        auto shopTurret2 = std::make_shared<ShopTurret>("turret2", 4, 200, 0.5f, "textures/TurretFire.png");
        shop.addTurret(shopTurret2);
        int width, height;
        glfwGetWindowSize(getWindow(), &width, &height);
        glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), -2.0f, 2.0f);
        glm::mat4 view = glm::mat4(1.0f);
        renderSystem.SetView(view);
        renderSystem.SetProjection(projection);
        renderSystem.start();
        renderer.setWindow(getWindow());

        InputManager::RegisterCallbacks(getWindow(), &inputManager);


        collisionSystem = std::make_unique<gl3::ecs::systems::CollisionSystem>();
        collisionSystem->setCallback([this](entt::entity a, entt::entity b) {
    handleEnemyProjectileCollosion(this->registry, a, b);
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

        std::vector<glm::vec2> PathCellIndices;
        for (int x = 0; x <= 28; ++x) {
            PathCellIndices.emplace_back(glm::vec2(x, 5.0f));
        }


        grid.MarkPathCells(PathCellIndices);

        entt::entity pathEntity = registry.create();
        path = std::make_shared<Path>(PathCellIndices, grid);
        registry.emplace<std::shared_ptr<Path>>(pathEntity, path);



    }

    void update(GLFWwindow* window) override {
        destroyBulletsOffScreen();
        destructionSystem->update();
        inputManager.Update();
        handleInputs(window);
        waveSystem->update();
        spawnSystem->update();
        movementSystem->update();
        targetingSystem->update();
        shootingSystem->update();
        audioSystem->update();
        checkBulletEnemyCollision();
    }

    void handleInputs(GLFWwindow* window)
    {
        if (inputManager.IsKeyPressed(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(window, 1);
        }
        if (inputManager.IsKeyPressed(GLFW_KEY_T)) {
            auto turretInfo = shop.getSelectedTurret();
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            int windowWidth, windowHeight;
            glfwGetWindowSize(window, &windowWidth, &windowHeight);
            ypos = windowHeight - ypos;

            entt::entity entity = registry.create();
            registry.emplace<gl3::ecs::components::Transform>(
                entity,
                glm::vec3(xpos - 100, ypos - 100, 1.0f),
                0.0f,
                glm::vec2(200.0f, 200.0f)
            );
            registry.emplace<gl3::ecs::components::Targeting>(entity);
            registry.emplace<gl3::ecs::components::Shooting>(entity, turretInfo->damage, turretInfo->range, turretInfo->cooldown);
            auto tex = std::make_shared<gl3::Texture>(gl3::resolveAssetPath(turretInfo->assetPath));
            registry.emplace<gl3::ecs::components::Sprite>(entity, tex, glm::vec4(1.0f));



        }
        if (inputManager.IsMouseButtonPressed(0))
        {
            std::cout << "M" << std::endl;
        }
    }
    void destroyBulletsOffScreen()
    {
        auto view = registry.view<gl3::ecs::components::Transform, gl3::ecs::components::BulletTag>();

        for (auto entity : view)
        {
            auto& transform = view.get<gl3::ecs::components::Transform>(entity);
            const auto& pos = transform.position;

            if (pos.x < 0 || pos.x > WIDTH || pos.y < 0 || pos.y > HEIGHT)
            {
                registry.emplace<gl3::ecs::components::DestroyRequest>(entity);
            }
        }
    }

    void checkBulletEnemyCollision()
    {
        auto bulletView = registry.view<gl3::ecs::components::Transform, gl3::ecs::components::CircleCollider, gl3::ecs::components::BulletTag>();
        auto enemyView  = registry.view<gl3::ecs::components::Transform, gl3::ecs::components::CircleCollider, gl3::ecs::components::EnemyTag>();

        for (auto bullet : bulletView)
        {
            const auto& bulletTransform = bulletView.get<gl3::ecs::components::Transform>(bullet);
            const auto& bulletCollider  = bulletView.get<gl3::ecs::components::CircleCollider>(bullet);

            for (auto enemy : enemyView)
            {
                const auto& enemyTransform = enemyView.get<gl3::ecs::components::Transform>(enemy);
                const auto& enemyCollider  = enemyView.get<gl3::ecs::components::CircleCollider>(enemy);

                glm::vec2 posA = bulletTransform.position;
                glm::vec2 posB = enemyTransform.position;

                float radiusA = bulletCollider.radius;
                float radiusB = enemyCollider.radius;

                float distanceSq = glm::dot(posA - posB, posA - posB);
                float radiiSum   = radiusA + radiusB;

                if (distanceSq <= radiiSum * radiiSum)
                {
                    handleEnemyProjectileCollosion(registry, enemy, bullet);
                    break;
                }
            }
        }
    }


    void draw() override {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderSystem.renderGrid(grid);
        renderSystem.render(registry);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        shop.draw();

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(getWindow(), &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

private:
    entt::registry registry;
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
    Shop shop;

    std::unique_ptr<DestructionSystem> destructionSystem;
    std::unique_ptr<gl3::ecs::systems::CollisionSystem> collisionSystem;
    std::shared_ptr<Path> path;
    InputManager inputManager;
};
