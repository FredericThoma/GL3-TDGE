#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "engine/Game.h"
#include "engine/rendering/Renderer.h"


namespace gl3::engine {
    using Context = context::Context;

    Game::Game(int width, int height, const std::string &title) :
            context(width, height, title) {
        audio.init();
        audio.setGlobalVolume(0.1f);
    }

    void Game::run() {
        std::cout << "Game running" << std::endl;
        start();
        context.run([&](Context &ctx){
            update(getWindow());
            draw();
            updateDeltaTime();
        });
    }

    void Game::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    glm::mat4 Game::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, scale);

        glm::mat4 view = glm::mat4(1.0f);
        int width, height;
        glfwGetWindowSize(context.getWindow(), &width, &height);
        glm::mat4 projection = glm::ortho(
            0.0f, static_cast<float>(width),
            0.0f, static_cast<float>(height),
            -1.0f, 1.0f
        );

        return projection * view * model;
    }

    Game::~Game() = default;
}