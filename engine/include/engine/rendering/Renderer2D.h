#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

namespace gl3::renderer {
    class Renderer2D {
    public:
        Renderer2D();
        ~Renderer2D();

        void drawQuad(const glm::mat4& mvp, const glm::vec4& color);

    private:
        unsigned int vao, vbo, ebo;
        Shader shader;
        Texture texture;
    };
}
