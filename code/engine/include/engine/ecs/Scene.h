#pragma once
#include <entt/entt.hpp>
#include "engine/rendering/Renderer.h"


namespace gl3::ecs {
    class Scene {
    public:
        entt::registry& getRegistry() { return registry; }
        void onUpdate(float dt);
        void onRender(renderer::Renderer& renderer);

    private:
        entt::registry registry;
    };
}
