#pragma once

#include <unordered_map>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/vec2.hpp"

class InputManager {
public:
    void Update();

    bool IsKeyPressed(int key) const;
    bool IsKeyDown(int key) const;
    bool IsKeyReleased(int key) const;

    bool IsMouseButtonPressed(int button) const;
    glm::vec2 GetMousePosition() const;

    void SetKeyState(int key, int action);
    void SetMouseButtonState(int button, int action);
    void SetMousePosition(double xpos, double ypos);

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);

    static void RegisterCallbacks(GLFWwindow* window, InputManager* inputManager);

private:
    std::unordered_map<int, bool> keysPressed;
    std::unordered_map<int, bool> keysDown;
    std::unordered_map<int, bool> keysReleased;
    std::unordered_map<int, bool> prevKeyState;

    std::unordered_map<int, bool> mouseButtons;
    glm::vec2 mousePos = glm::vec2(0.0f);
};
