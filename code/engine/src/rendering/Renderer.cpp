
#include "engine/rendering/Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "engine/rendering/Assets.h"
#include "GLFW/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"


namespace gl3::renderer {

    Renderer::Renderer()
    :shader(
         resolveAssetPath("shaders/vertexShader.vert"),
         resolveAssetPath("shaders/fragmentShader.frag")
     ), texture(resolveAssetPath("textures/turret_placeholder.png"), 0)
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

    void Renderer::drawQuad(const glm::mat4& mvp, const glm::vec4& color) const {
        shader.use();
        shader.setMatrix("u_MVP", mvp);
        shader.setVector("u_Color", color);

        shader.setBool("u_UseTexture", false);


        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void Renderer::drawTexturedQuad(const glm::mat4& mvp, const Texture* texture, const glm::vec4& tint) const
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


    void Renderer::drawMouse(Texture& texture) const
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int winWidth, winHeight;
        glfwGetWindowSize(window, &winWidth, &winHeight);

        float x = static_cast<float>(xpos);
        float y = static_cast<float>(winHeight - ypos);

        float quadWidth = 32.0f;
        float quadHeight = 32.0f;


        glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(winWidth), 0.0f, static_cast<float>(winHeight));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 1.0f));
        model = glm::scale(model, glm::vec3(quadWidth, quadHeight, 1.0f));

        glm::mat4 mvp = proj * model;

        drawTexturedQuad(mvp, &texture, glm::vec4(1.0f));
    }

    void Renderer::drawUI(const UserInterface& userInterface) const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec2 uv0 = ImVec2(0.0f, 0.0f);
        ImVec2 uv1 = ImVec2(1.0f, 1.0f);

        // Optional padding & tint
        int frame_padding = -1; // -1 uses default padding
        ImVec4 bg_col = ImVec4(0, 0, 0, 0);      // transparent background
        ImVec4 tint_col = ImVec4(1, 1, 1, 1);    // full color

        for (auto &uie : userInterface.elements)
        {
            ImGui::Begin(uie.title.c_str());

            for (auto &uii : uie.images)
            {
                auto texID = uii.texture.getID();
                if (ImGui::ImageButton("test", (void*)static_cast<intptr_t>(texID), ImVec2(100, 100),uv0, uv1, bg_col, tint_col))
                {
                    // Handle click
                    ImGui::Text("ImageButton clicked!");
                }
            }
            for (auto &uit : uie.texts)
            {

                ImGui::Text("%s", uit.text.c_str());

            }
            for (auto uiib: uie.imageButtons)
            {
                ImGui::SameLine();
                if (ImGui::ImageButton(uiib->id.c_str(), (void*)static_cast<intptr_t>(uiib->texture.getID()), uiib->scale,uiib->uv0, uiib->uv1, uiib->bg_col, uiib->tint_col))
                {
                    uiib->onClick();
                }
            }
            ImGui::End();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    Renderer::~Renderer() {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteVertexArrays(1, &vao);
    }

    void Renderer::setWindow(GLFWwindow* win) {
        window = win;
    }
}
