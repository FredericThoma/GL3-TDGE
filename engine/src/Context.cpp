#include <stdexcept>
#include "engine/Context.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <chrono>
#include <thread>

#include "engine/rendering/Assets.h"
#include "engine/rendering/Texture.h"
#include "engine/rendering/UserInterface.h"

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
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void Context::run(const Context::Callback& update) {
        int targetFPS = 60;
        double frameDuration = 1.0 / targetFPS;

        while (!glfwWindowShouldClose(window)) {
            double frameStartTime = glfwGetTime();

            glClearColor(0.172f, 0.243f, 0.313f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glfwPollEvents();

            // Update happens here
            update(*this);

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
