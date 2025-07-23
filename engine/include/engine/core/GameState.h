#pragma once

class GameState {
public:
    enum class State {
        Playing,
        Paused,
        Menu,
    };

    static GameState& getInstance();

    void setState(State state);
    State getState() const;

    void setFPS(float fps);
    float getFPS() const;

private:
    GameState();
    State currentState;
    float currentFPS;
};