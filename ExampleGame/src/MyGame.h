#include "engine/Game.h"
#include "Player.h"
#include "Score.h"
#include "GameOverScreen.h"
#include "engine/rendering/Renderer2D.h"

class MyGame : public gl3::engine::Game {
public:
    MyGame() : Game(1280, 960, "My 2D Game"),
               score(player),
               gameOverScreen(player) {}

    void start() override {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void update(GLFWwindow* window) override {
        // TODO
    }

    void draw() override {
        glClear(GL_COLOR_BUFFER_BIT);

        glm::vec3 position = {100.0f, 100.0f, 0.0f};
        float rotation = 0.0f;
        glm::vec3 scale = {100.0f, 100.0f, 1.0f};

        glm::mat4 mvp = calculateMvpMatrix(position, rotation, scale);
        glm::vec4 color = {0.9f, 0.9f, 0.9f, 1.0f};
        renderer.drawQuad(mvp, color);
    }

private:
    Player player;
    Score score;
    GameOverScreen gameOverScreen;
    gl3::renderer::Renderer2D renderer;

};
