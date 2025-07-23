#include "engine/core/InputManager.h"
#include <GLFW/glfw3.h>

void InputManager::Update() {
    keysPressed.clear();
    keysReleased.clear();

    for (const auto& [key, isDown] : keysDown) {
        bool wasDown = prevKeyState[key];
        if (!wasDown && isDown) keysPressed[key] = true;
        if (wasDown && !isDown) keysReleased[key] = true;

        prevKeyState[key] = isDown;
    }
}

bool InputManager::IsKeyPressed(int key) const {
    auto it = keysPressed.find(key);
    return it != keysPressed.end() && it->second;
}

bool InputManager::IsKeyDown(int key) const {
    auto it = keysDown.find(key);
    return it != keysDown.end() && it->second;
}

bool InputManager::IsKeyReleased(int key) const {
    auto it = keysReleased.find(key);
    return it != keysReleased.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(int button) const {
    auto it = mouseButtons.find(button);
    return it != mouseButtons.end() && it->second;
}

glm::vec2 InputManager::GetMousePosition() const {
    return mousePos;
}

void InputManager::SetKeyState(int key, int action) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        keysDown[key] = true;
    } else if (action == GLFW_RELEASE) {
        keysDown[key] = false;
    }
}

void InputManager::SetMouseButtonState(int button, int action) {
    if (action == GLFW_PRESS) {
        mouseButtons[button] = true;
    } else if (action == GLFW_RELEASE) {
        mouseButtons[button] = false;
    }
}

void InputManager::SetMousePosition(double xpos, double ypos) {
    mousePos = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input && key >= 0) {
        input->SetKeyState(key, action);
    }
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input) {
        input->SetMouseButtonState(button, action);
    }
}

void InputManager::CursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (input) {
        input->SetMousePosition(xpos, ypos);
    }
}

void InputManager::RegisterCallbacks(GLFWwindow* window, InputManager* inputManager) {
    glfwSetWindowUserPointer(window, inputManager);
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
}
