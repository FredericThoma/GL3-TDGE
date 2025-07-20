#pragma once

#include <entt/entt.hpp>
#include "engine/rendering/Renderer.h"
#include "engine/ecs/components/Transform.h"
#include "engine/ecs/components/Sprite.h"

namespace gl3::ecs::systems {

    class RenderSystem {
    public:
        explicit RenderSystem(gl3::renderer::Renderer& renderer);

        void render(entt::registry& registry, const glm::mat4& cameraViewProj);

    private:
        gl3::renderer::Renderer& renderer;
    };

}
