#include "../../include/engine/core/GameState.h"

GameState::GameState() : currentState(State::Playing), currentFPS(60.0f) {}

GameState& GameState::getInstance() {
    static GameState instance;
    return instance;
}

void GameState::setState(State state) {
    currentState = state;
}

GameState::State GameState::getState() const {
    return currentState;
}

void GameState::setFPS(float fps) {
    currentFPS = fps;
}

float GameState::getFPS() const {
    return currentFPS;
}
