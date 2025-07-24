add_library(imgui INTERFACE)

target_include_directories(imgui INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
)
