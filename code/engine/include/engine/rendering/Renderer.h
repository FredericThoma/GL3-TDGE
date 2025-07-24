#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "UserInterface.h"
#include "GLFW/glfw3.h"

namespace gl3::renderer {
    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void setWindow(GLFWwindow* window);

        void drawQuad(const glm::mat4& mvp, const glm::vec4& color) const;
        void drawTexturedQuad(const glm::mat4& mvp, const Texture* texture, const glm::vec4& tint) const;
        void drawMouse(Texture& texture) const;
        void drawUI(const UserInterface& userInterface) const;

    private:
        unsigned int vao, vbo, ebo;
        Shader shader;
        Texture texture;
        GLFWwindow* window = nullptr;
    };
}
