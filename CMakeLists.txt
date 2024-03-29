cmake_minimum_required(VERSION 3.26)
set(PROJECT_NAME minecraft_clone)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

file(GLOB IMGUI_SOURCE
        "lib/imgui/*.h"
        "lib/imgui/*.cpp"
        "lib/imgui/backends/imgui_impl_opengl3.h"
        "lib/imgui/backends/imgui_impl_opengl3.cpp"
        "lib/imgui/backends/imgui_impl_glfw.h"
        "lib/imgui/backends/imgui_impl_glfw.cpp"
)

add_executable(${PROJECT_NAME}
        lib/glad/src/glad.c
        lib/stb/src/stb_image.cpp
        ${IMGUI_SOURCE}
        src/run.cpp
        src/window/window.cpp
        src/window/window.hpp
        src/graphics/shader/shader.cpp
        src/graphics/shader/shader.hpp
        src/graphics/texture/texture.cpp
        src/graphics/texture/texture.hpp
        src/graphics/render/render.cpp
        src/graphics/render/render.hpp
        src/gui/gui.cpp
        src/gui/gui.hpp
        src/gui/screens/debug.cpp
        src/gui/screens/debug.hpp
        src/graphics/models/cube/cube.cpp
        src/graphics/models/cube/cube.hpp
        src/graphics/buffer/VertexBuffer.cpp
        src/graphics/buffer/VertexBuffer.hpp
        src/graphics/buffer/VertexArray.cpp
        src/graphics/buffer/VertexArray.hpp
)

include_directories(lib/glad/include)
include_directories(lib/stb/include)
include_directories(lib/glm/include)
include_directories(lib/imgui)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
