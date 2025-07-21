#include "engine/ecs/systems/RenderSystem.h"

#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include "engine/rendering/Renderer.h"

namespace gl3::ecs::systems {

    RenderSystem::RenderSystem(gl3::renderer::Renderer& renderer,
                           const glm::mat4& projection,
                           const glm::mat4& view)
    : renderer(renderer),
      projectionMatrix(projection),
      viewMatrix(view) {}


    void RenderSystem::render(entt::registry& registry) {
        auto view = registry.view<components::Transform, components::Sprite>();

        glm::mat4 viewProj = projectionMatrix * viewMatrix;

        for (auto entity : view) {
            const auto& transform = view.get<components::Transform>(entity);
            std::cout << transform.position.x << " " << transform.position.y << std::endl;
            const auto& sprite = view.get<components::Sprite>(entity);

            glm::mat4 model = transform.getTransformMatrix();
            glm::mat4 mvp = viewProj * model;
            renderer.drawTexturedQuad(mvp, sprite.texture.get(), sprite.color);
        }
    }

    void RenderSystem::renderGrid(Grid grid)
    {
        auto allCells = grid.getAllCells();
        glm::vec4 color = glm::vec4(1.0f);
        for (auto cell : allCells)
        {

            switch (cell.type)
            {
                case CellType::Path:
                color = glm::vec4(0.788f, 0.537f, 0.071f, 1.0f);
                break;
                default:
                color = glm::vec4(0.2f, 0.2f, 1.0f, 1.0f);
break;
            }
            glm::mat4 viewProj = projectionMatrix * viewMatrix;
            glm::vec3 pos3D = cell.worldPosition;
            glm::mat4 model = glm::translate(glm::mat4(1.0f), pos3D);
            model = glm::scale(model, glm::vec3(grid.GetCellSize(), grid.GetCellSize(), 1.0f));
            glm::mat4 mvp = viewProj * model;
            renderer.drawQuad(mvp, color);
        }
    }

    void RenderSystem::renderChessboard(int boardWidth, int boardHeight, float tileSizeX, float tileSizeY) {
        glm::mat4 viewProj = projectionMatrix * viewMatrix;

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(tileSizeX, tileSizeY, 1.0f));

        for (int y = 0; y < boardHeight; ++y) {
            float posY = y * tileSizeY;
            for (int x = 0; x < boardWidth; ++x) {
                float posX = x * tileSizeX;

                glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0.0f));
                glm::mat4 model = translateMatrix * scaleMatrix;

                glm::mat4 mvp = viewProj * model;

                glm::vec4 color = ((x + y) % 2 == 0) ? glm::vec4(1.0f) : glm::vec4(0.0f);

                renderer.drawQuad(mvp, color);
            }
        }
    }

    void RenderSystem::renderChessboard2(int boardWidth, int boardHeight, float tileSizeX, float tileSizeY, const glm::mat4& viewProj) {
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(tileSizeX, tileSizeY, 1.0f));

        for (int y = 0; y < boardHeight; ++y) {
            float posY = y * tileSizeY;
            for (int x = 0; x < boardWidth; ++x) {
                float posX = x * tileSizeX;

                glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posX, posY, 0.0f));
                glm::mat4 model = translateMatrix * scaleMatrix;

                glm::mat4 mvp = viewProj * model;

                glm::vec4 color = ((x + y) % 2 == 0) ? glm::vec4(1.0f) : glm::vec4(0.0f);

                renderer.drawQuad(mvp, color);
            }
        }

    }

    void RenderSystem::renderOverlappingTiles(float tileSizeX, float tileSizeY) {
        glm::mat4& viewProj = viewMatrix * projectionMatrix;

        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(tileSizeX, tileSizeY, 1.0f));

        // Tile 1: RED, in front (Z = 0.0)
        glm::mat4 translateRed = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f)); // Adjust X/Y if needed
        glm::mat4 modelRed = translateRed * scaleMatrix;
        renderer.drawQuad(viewProj * modelRed, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        // Tile 2: GREEN, behind (Z = -0.5)
        glm::mat4 translateGreen = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.5f));
        glm::mat4 modelGreen = translateGreen * scaleMatrix;
        renderer.drawQuad(viewProj * modelGreen, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }





}
