#pragma once
struct Movement {
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    float maxSpeed = 10.0f;
    bool canMove = true;
    bool isMoving = false;
};
