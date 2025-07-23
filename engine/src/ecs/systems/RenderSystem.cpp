#include "engine/ecs/systems/RenderSystem.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "engine/rendering/Assets.h"
#include "engine/rendering/Renderer.h"

namespace gl3::ecs::systems {

    RenderSystem::RenderSystem(gl3::renderer::Renderer& renderer,
                           const glm::mat4& projection,
                           const glm::mat4& view)
    : renderer(renderer),
      projectionMatrix(projection),
      viewMatrix(view) {}


    void RenderSystem::start()
    {
        pathTexture = Texture(resolveAssetPath("textures/PathTexture.png"));
        wieseTexture = Texture(resolveAssetPath("textures/Grass.png"));
        mouseTexture = Texture(resolveAssetPath("textures/Bullet.png"));
    }


    void RenderSystem::render(entt::registry& registry) {
        auto view = registry.view<components::Transform, components::Sprite>();

        glm::mat4 viewProj = projectionMatrix * viewMatrix;

        for (auto entity : view) {
            const auto& transform = view.get<components::Transform>(entity);
            const auto& sprite = view.get<components::Sprite>(entity);

            glm::mat4 model = transform.getTransformMatrix();
            glm::mat4 mvp = viewProj * model;
            renderer.drawTexturedQuad(mvp, sprite.texture.get(), sprite.color);
        }

        //renderer.drawMouse(mouseTexture);
    }


    void RenderSystem::renderGrid(const Grid& grid)
    {
        glm::mat4 viewProj = projectionMatrix * viewMatrix;

        auto allCells = grid.getAllCells();
        for (auto cell : allCells)
        {
            glm::vec3 pos3D = cell->worldPosition;
            glm::mat4 model = glm::translate(glm::mat4(1.0f), pos3D);
            model = glm::scale(model, glm::vec3(grid.GetCellSize(), grid.GetCellSize(), 1.0f));
            glm::mat4 mvp = viewProj * model;

            renderer.drawTexturedQuad(mvp, &wieseTexture, glm::vec4(1.0f));

            if (cell->type == CellType::Path)
            {
                glm::vec3 scaleFactor(1.0f, 1.0f, 1.0f);

                // Apply scaling and slight Z-offset
                glm::mat4 modelScaled = glm::scale(model, scaleFactor);
                glm::mat4 modelOffset = glm::translate(modelScaled, glm::vec3(0.0f, 0.0f, 0.001f));
                glm::mat4 mvpOffset = viewProj * modelOffset;

                renderer.drawTexturedQuad(mvpOffset, &pathTexture, glm::vec4(1.0f));
            }
        }
    }



}
