#pragma once

#include <glm/glm.hpp>
#include "engine/rendering/Texture.h"

namespace gl3::ecs::components {

    struct Sprite {
        std::shared_ptr<Texture> texture = nullptr;
        glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

        Sprite() = default;

        Sprite(std::shared_ptr<Texture> tex, const glm::vec4& tint = {1, 1, 1, 1})
            : texture(std::move(tex)), color(tint) {}
    };

}
