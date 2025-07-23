#pragma once

namespace gl3::ecs::components
{
    struct CircleCollider
    {
        float radius;

        CircleCollider(float r) : radius(r) {}
    };

    struct RectangleCollider
    {
        float width;
        float height;

        RectangleCollider(float w, float h) : width(w), height(h) {}
    };
}
