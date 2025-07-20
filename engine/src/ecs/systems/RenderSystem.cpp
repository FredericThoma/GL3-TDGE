#include "engine/ecs/systems/RenderSystem.h"
#include <glm/gtx/string_cast.hpp>
#include "engine/rendering/Renderer.h"

namespace gl3::ecs::systems {

    RenderSystem::RenderSystem(gl3::renderer::Renderer& renderer)
        : renderer(renderer) {}

    void RenderSystem::render(entt::registry& registry, const glm::mat4& cameraViewProj) {
        auto view = registry.view<components::Transform, components::Sprite>();

        for (auto entity : view) {
            const auto& transform = view.get<components::Transform>(entity);
            const auto& sprite = view.get<components::Sprite>(entity);

            glm::mat4 model = transform.getTransformMatrix();
            glm::mat4 mvp = cameraViewProj * model;
            renderer.drawTexturedQuad(mvp,sprite.texture.get(), sprite.color);
        }
    }

}
