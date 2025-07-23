cmake_minimum_required(VERSION 3.18)

project(Engine)

file(GLOB_RECURSE HEADER_LIST CONFIGURE_DEPENDS "include/**.h")
file(GLOB_RECURSE PRIVATE_HEADER_LIST CONFIGURE_DEPENDS "src/**.h")
file(GLOB_RECURSE SOURCE_LIST CONFIGURE_DEPENDS "src/**.cpp")
file(GLOB IMGUI_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/extern/imgui/imgui*.cpp
        ${CMAKE_SOURCE_DIR}/extern/imgui/backends/imgui_impl_glfw.cpp
        ${CMAKE_SOURCE_DIR}/extern/imgui/backends/imgui_impl_opengl3.cpp
)

set(ENGINE_NAME Engine)

add_library(${ENGINE_NAME}
        ${HEADER_LIST}
        ${PRIVATE_HEADER_LIST}
        ${SOURCE_LIST}
        ${IMGUI_SOURCES}
        include/engine/rendering/UserInterface.h
        include/engine/core/GameState.cpp
        include/engine/core/GameState.h
)

target_compile_features(${ENGINE_NAME} PRIVATE cxx_std_17)

target_include_directories(${ENGINE_NAME} PUBLIC
        include
        ${CMAKE_SOURCE_DIR}/extern/imgui
        ${CMAKE_SOURCE_DIR}/extern/imgui/backends
)

target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw glm soloud tinygltf entt nlohmann_json imgui)

target_compile_definitions(${ENGINE_NAME} PUBLIC ASSET_ROOT=${CMAKE_SOURCE_DIR}/assets)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "Public Header" FILES ${HEADER_LIST})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" PREFIX "Source" FILES ${SOURCE_LIST})
