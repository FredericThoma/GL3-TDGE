# Getting started

This is a simple quick start guide how to start developing games with this engine.

Make sure you followed the steps in QuickStart.md

## Minimal Setup

1. Create new folder in project root 'MyAwesomeGame' and 'CMakeLists.txt' inside that folder
2. Create a folder 'MyAwesomeGame/src'
3. In project root: Open "CMakeLists.txt" and add this line:
```cmake
add_subdirectory(MyAwesomeGame)
```
4. In MyAwesomeGame/src: Create 3 Files: 'main.cpp', 'MyAwesomeGame.h'

### MyAwesomeGame/src/MyAwesomeGame.h
```c++
#pragma once

#include "engine/Game.h"

using namespace gl3::engine;

class MyAwesomeGame : public Game
{
public:

    MyAwesomeGame()
        : Game(1280, 1280, "My 2D Game")
    {
    }

void start() override
    {
        // This runs once, when the game is started
    }

    void update(GLFWwindow* window) override
    {
        // This runs every frame
    }

    void draw() override
    {
        // this runs every frame after update
    }
};
```
### MyAwesomeGame/src/main.cpp
```c++
#include "MyAwesomeGame.h"

int main() {
    auto game = new MyAwesomeGame();
    game->run();
}
```
5. In dir 'MyAwesomeGame': Open 'CMakeLists.txt' and add the following content:

### MyAwesomeGame/CMakeLists.txt
```cmake
cmake_minimum_required(VERSION 3.18)

set(SOURCE_FILES src/main.cpp)
set(EXE_FILE MyAwesomeGame)

add_executable(${EXE_FILE} ${SOURCE_FILES})

target_compile_features(${EXE_FILE} PRIVATE cxx_std_17)

target_link_libraries(${EXE_FILE} PRIVATE Engine)

```

6. Reload CMake Project -> Build -> Run

**That's it! You are now ready to start developing your Game!**

# Next Steps:

## Create a Scene & Add GameObjects

We first need to create a Scene and get the Scenes registry. The registry is responsible for storing and handling Entites(a.k.a GameObjects) and their Components.
Then we can add GameObjects to our Scene via 'registry->create()'
```c++
#pragma once

#include "engine/Game.h"
#include "engine/ecs/Scene.h"
#include "tiny_gltf/tiny_gltf.h"

using namespace gl3::engine;

class MyAwesomeGame : public Game
{
public:

    MyAwesomeGame()
        : Game(1280, 1280, "My 2D Game")
    {
    }

void start() override
{
// Instantiate a new Scene and get it's registry
scene = gl3::ecs::Scene();
registry = &scene.getRegistry();

        // Define our first GameObject
        entt::entity gameObject = registry->create();

    }

    void update(GLFWwindow* window) override
    {
        // This runs every frame
    }

    void draw() override
    {
        // this runs every frame after update
    }

private:
gl3::ecs::Scene scene;
entt::registry *registry;
};
```

## Attach Components to GameObjects

You can add all components in engine/ecs/components to GameObjects. These are later used by the Systems to act on entities which have specific components.
This is an example of how to add an "Transform" Component as well as a "Sprite" Component to a GameObject. those are the prerequisites for rendering them.
```c++
entt::entity entity = registry.create();
        registry.emplace<gl3::ecs::components::Transform>(
            entity,
            glm::vec3(500.0, 500.0f, 1.0f),
            0.0f,
            glm::vec2(300.0f, 300.0f)
        );
        registry.emplace<gl3::ecs::components::Targeting>(entity);

```

### WaveSystem Setup

To set up the WaveSystem:

```c++
void start(){
// ...
auto waveSystem = std::make_unique<WaveSystem>(registry);
auto all_waves = waveSystem->allWavesFromJson(gl3::resolveAssetPath("wave_definition_test.json"));
waveSystem->setWaves(all_waves);
waveSystem->resetWaves();
// ...
}

void update(){
waveSystem->update();
}

```

You are now ready to define your waves via "/assets/wave_definition_test.json"

### Next Steps:

- Set up the renderSystem (similar to waveSystem, feel free to take a look at the docs)
- call it in Update to render all entities with Sprite and Transform Component
- Define a Path that enemies can follow
- Attach colliders / MovementComponents
- ...
- Have Fun!
- 