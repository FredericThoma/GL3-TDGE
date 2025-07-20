#include "engine/Game.h"
#include "Player.h"
#include "Score.h"
#include "GameOverScreen.h"
#include "engine/rendering/Texture.h"
#include "engine/rendering/Renderer.h"
#include "engine/ecs/Scene.h"
#include "engine/ecs/systems/RenderSystem.h"
#include "engine/ecs/components/Transform.h"
#include "engine/rendering/Assets.h"
#include "engine/ecs/components/Sprite.h"

class MyGame : public gl3::engine::Game {
public:
    MyGame()
        : Game(1280, 960, "My 2D Game"),
          scene(),
          renderSystem(renderer){}

    void start() override {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        entt::registry& registry = scene.getRegistry();

        entt::entity entity = registry.create();

        registry.emplace<gl3::ecs::components::Transform>(
            entity,
            glm::vec2(0.0f, 0.0f),
            0.0f,
            glm::vec2(100.0f, 100.0f)
        );

        glm::vec4 color = {1.0f, 1.0f, 0.0f, 1.0f};

        auto texture = std::make_shared<gl3::Texture>(gl3::resolveAssetPath("textures/turret_placeholder.png"));
        registry.emplace<gl3::ecs::components::Sprite>(entity, texture, color);

    }

    void update(GLFWwindow* window) override {
        // TODO: Input, game logic
    }

    void draw() override {
        glClear(GL_COLOR_BUFFER_BIT);
        int width, height;
        glfwGetWindowSize(getWindow(), &width, &height);

        glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height), -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        entt::registry& registry = scene.getRegistry();
        renderSystem.render(registry, projection * view);

    }
private:

    gl3::renderer::Renderer renderer;

    gl3::ecs::Scene scene;
    gl3::ecs::systems::RenderSystem renderSystem;
};
