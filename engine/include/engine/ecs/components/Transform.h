#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gl3::ecs::components {

    struct Transform {
        glm::vec2 position = {0.0f, 0.0f};
        float rotation = 0.0f; // degrees
        glm::vec2 scale = {1.0f, 1.0f};

        glm::mat4 getTransformMatrix() const {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position, 0.0f));
            model = glm::rotate(model, glm::radians(rotation), {0.0f, 0.0f, 1.0f});
            model = glm::scale(model, glm::vec3(scale, 1.0f));
            return model;
        }
    };

}
