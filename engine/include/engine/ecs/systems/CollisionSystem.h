#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <functional>
#include "engine/ecs/components/Collider.h"
#include "engine/ecs/components/Transform.h"

namespace gl3::ecs::systems
{
    class CollisionSystem
    {
    public:
        using CollisionCallback = std::function<void(entt::entity, entt::entity)>;

        explicit CollisionSystem(CollisionCallback callback = nullptr)
            : onCollision(callback) {}

        void setCallback(CollisionCallback callback)
        {
            onCollision = std::move(callback);
        }


        void update(entt::registry& registry)
        {
            auto view = registry.view<components::Transform>();

            view.each([&](entt::entity entityA, components::Transform& transformA)
            {
                if (registry.all_of<components::CircleCollider>(entityA)) {
                    auto& circleA = registry.get<components::CircleCollider>(entityA);

                    view.each([&](entt::entity entityB, components::Transform& transformB)
                    {
                        if (entityA >= entityB) return;

                        if (registry.all_of<components::CircleCollider>(entityB)) {
                            auto& circleB = registry.get<components::CircleCollider>(entityB);
                            if (checkCircleCircle(transformA.position, circleA.radius,
                                                  transformB.position, circleB.radius)) {
                                handleCollision(entityA, entityB);
                            }
                        }

                        else if (registry.all_of<components::RectangleCollider>(entityB)) {
                            auto& rectB = registry.get<components::RectangleCollider>(entityB);
                            if (checkCircleRect(transformA.position, circleA.radius,
                                                transformB.position, rectB.width, rectB.height)) {
                                handleCollision(entityA, entityB);
                            }
                        }
                    });
                }

                else if (registry.all_of<components::RectangleCollider>(entityA)) {
                    auto& rectA = registry.get<components::RectangleCollider>(entityA);

                    view.each([&](entt::entity entityB, components::Transform& transformB)
                    {
                        if (entityA >= entityB) return;

                        if (registry.all_of<components::RectangleCollider>(entityB)) {
                            auto& rectB = registry.get<components::RectangleCollider>(entityB);
                            if (checkRectRect(transformA.position, rectA.width, rectA.height,
                                              transformB.position, rectB.width, rectB.height)) {
                                handleCollision(entityA, entityB);
                            }
                        }
                    });
                }
            });
        }

    private:
        CollisionCallback onCollision;

        void handleCollision(entt::entity a, entt::entity b)
        {

            if (onCollision) {
                std::cout << "handleCollision called\n" <<std::endl;
                onCollision(a, b);
            }
        }

        bool checkCircleCircle(const glm::vec2& posA, float radiusA,
                               const glm::vec2& posB, float radiusB)
        {
            float distanceSq = glm::dot(posA - posB, posA - posB);
            float radiiSum = radiusA + radiusB;
            return distanceSq <= radiiSum * radiiSum;
        }

        bool checkRectRect(const glm::vec2& posA, float widthA, float heightA,
                           const glm::vec2& posB, float widthB, float heightB)
        {
            return !(posA.x + widthA / 2 < posB.x - widthB / 2 ||
                     posA.x - widthA / 2 > posB.x + widthB / 2 ||
                     posA.y + heightA / 2 < posB.y - heightB / 2 ||
                     posA.y - heightA / 2 > posB.y + heightB / 2);
        }

        bool checkCircleRect(const glm::vec2& circlePos, float radius,
                             const glm::vec2& rectPos, float rectWidth, float rectHeight)
        {
            glm::vec2 rectHalfExtents = { rectWidth / 2.0f, rectHeight / 2.0f };
            glm::vec2 diff = circlePos - rectPos;
            glm::vec2 clamped = glm::clamp(diff, -rectHalfExtents, rectHalfExtents);
            glm::vec2 closest = rectPos + clamped;
            float distanceSq = glm::dot(circlePos - closest, circlePos - closest);
            return distanceSq <= radius * radius;
        }
    };
}
