cmake_minimum_required(VERSION 3.18)

project(Engine)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")

set(ENGINE_NAME Engine)

add_library(${ENGINE_NAME}
        ${HEADER_LIST}
        ${PRIVATE_HEADER_LIST}
        ${SOURCE_LIST}
        include/engine/rendering/Texture.h
        src/rendering/Texture.cpp
        include/engine/ecs/Scene.h
        include/engine/ecs/components/Transform.h
        include/engine/ecs/components/Sprite.h
        include/engine/ecs/systems/RenderSystem.h
        src/ecs/systems/RenderSystem.cpp
        include/engine/ecs/components/Tags.h
        include/engine/waves/WaveDefinition.h
        src/waves/WaveDefinition.cpp
        src/ecs/systems/WaveSystem.cpp
        include/engine/ecs/systems/WaveSystem.h
        include/engine/ecs/components/WaveState.h
        src/core/Grid.cpp
        include/engine/core/Grid.h
        src/core/Cell.cpp
        include/engine/ecs/components/Path.h
        include/engine/ecs/systems/MovementSystem.cpp
        include/engine/ecs/systems/MovementSystem.h
        include/engine/ecs/components/GridPosition.h
        include/engine/core/PathData.h
        include/engine/core/Cell.h
)

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)

target_include_directories(${ENGINE_NAME} PUBLIC include)

target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw glm soloud tinygltf entt nlohmann_json)

target_compile_definitions(${ENGINE_NAME} PUBLIC ASSET_ROOT=${CMAKE_SOURCE_DIR}/assets)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Public Header" FILES ${HEADER_LIST})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCE_LIST})
