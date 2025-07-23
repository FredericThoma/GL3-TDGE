#pragma once

#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

namespace gl3::renderer {
    class Renderer {
    public:
        Renderer();
        ~Renderer();

        void drawQuad(const glm::mat4& mvp, const glm::vec4& color);
        void drawTexturedQuad(const glm::mat4& mvp, const Texture* texture, const glm::vec4& tint);

    private:
        unsigned int vao, vbo, ebo;
        Shader shader;
        Texture texture;
    };
}
