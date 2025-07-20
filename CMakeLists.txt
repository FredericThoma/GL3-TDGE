cmake_minimum_required(VERSION 3.21)
project(tdge)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/glad)
add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/soloud)
add_subdirectory(extern/tinygltf)
add_subdirectory(extern/entt)
add_subdirectory(engine)

add_subdirectory(ExampleGame)
