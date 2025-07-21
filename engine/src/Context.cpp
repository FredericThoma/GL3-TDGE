#include <stdexcept>
#include "engine/Context.h"

#include <chrono>
#include <thread>

namespace gl3::engine::context {
    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Context::Context(int width, int height, const std::string &title) {
        if(!glfwInit()) {
            throw std::runtime_error("Failed to initialize glfw");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if(window == nullptr) {
            throw std::runtime_error("Failed to create window");
        }

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        glEnable(GL_DEPTH_TEST);
        if(glGetError() != GL_NO_ERROR) {
            throw std::runtime_error("gl error");
        }
    }

    void Context::run(const Context::Callback& update) {
        int targetFPS = 60;
        double frameDuration = 1.0 / targetFPS;

        while (!glfwWindowShouldClose(window)) {
            double frameStartTime = glfwGetTime();

            glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            update(*this); // This runs Game::update() and Game::draw()

            glfwSwapBuffers(window);
            glfwPollEvents();

            // FPS limiting
            double frameEndTime = glfwGetTime();
            double elapsed = frameEndTime - frameStartTime;
            double sleepTime = frameDuration - elapsed;

            if (sleepTime > 0.0) {
                std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
            }
        }
    }

    Context::~Context() {
        glfwTerminate();
    }
}
