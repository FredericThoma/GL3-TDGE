#include "../../include/engine/rendering/Renderer.h"

#include <iostream>
#include <glad/glad.h>
#include "../../include/engine/rendering/Assets.h"
#include "../../include/engine/rendering/Texture.h"

namespace gl3::renderer {

    Renderer::Renderer()
    : shader(
    resolveAssetPath("shaders/vertexShader.vert"),
    resolveAssetPath("shaders/fragmentShader.frag")
    ),
          texture(resolveAssetPath("textures/turret_placeholder.png"), 0)
    {
        float vertices[] = {
            0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
            1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
            1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
            0.0f, 1.0f, 0.0f,  0.0f, 1.0f
        };

        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // texture coords
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    void Renderer::drawQuad(const glm::mat4& mvp, const glm::vec4& color) {
        shader.use();
        shader.setMatrix("u_MVP", mvp);
        shader.setVector("u_Color", color);

        shader.setBool("u_UseTexture", false);


        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Renderer::drawTexturedQuad(const glm::mat4& mvp, const Texture* texture, const glm::vec4& tint)
 {
        shader.use();
        shader.setMatrix("u_MVP", mvp);
        shader.setVector("u_Color", tint);

        glActiveTexture(GL_TEXTURE0);
        texture->bind(0);
        shader.setBool("u_UseTexture", true);
        shader.setInt("u_Texture", 0);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }



    Renderer::~Renderer() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }
}
