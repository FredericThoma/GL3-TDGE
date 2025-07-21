#pragma once

#include <entt/entt.hpp>
#include "engine/rendering/Renderer.h"
#include "engine/ecs/components/Transform.h"
#include "engine/ecs/components/Sprite.h"

namespace gl3::ecs::systems {

    class RenderSystem {
    public:
        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;


        explicit RenderSystem(gl3::renderer::Renderer& renderer,
                      const glm::mat4& projection = glm::mat4(1.0f),
                      const glm::mat4& view = glm::mat4(1.0f));

        void renderOverlappingTiles(float tileSizeX, float tileSizeY);
        void render(entt::registry& registry);
        void renderChessboard(int boardWidth, int boardHeight, float tileSizeX, float tileSizeY);
        void RenderSystem::renderChessboard2(int boardWidth, int boardHeight, float tileSizeX, float tileSizeY, const glm::mat4& viewProj);
        void SetProjection(const glm::mat4& proj) {
            projectionMatrix = proj;
        }

        const glm::mat4& GetProjection() const {
            return projectionMatrix;
        }

        void SetView(const glm::mat4& view) {
            viewMatrix = view;
        }

        const glm::mat4& GetView() const {
            return viewMatrix;
        }

        gl3::renderer::Renderer& getRenderer()
        {
            return renderer;
        }


    private:
        gl3::renderer::Renderer& renderer;
    };

}
