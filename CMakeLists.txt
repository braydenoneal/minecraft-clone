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
        src/Run.cpp
        src/window/Window.cpp
        src/window/Window.hpp
        src/graphics/shader/Shader.cpp
        src/graphics/shader/Shader.hpp
        src/graphics/texture/Texture.cpp
        src/graphics/texture/Texture.hpp
        src/gui/Gui.cpp
        src/gui/Gui.hpp
        src/gui/screens/DebugScreen.cpp
        src/gui/screens/DebugScreen.hpp
        src/graphics/models/cube/Cube.cpp
        src/graphics/models/cube/Cube.hpp
        src/graphics/buffer/VertexBuffer.cpp
        src/graphics/buffer/VertexBuffer.hpp
        src/graphics/buffer/VertexArray.cpp
        src/graphics/buffer/VertexArray.hpp
        src/graphics/Graphics.cpp
        src/graphics/Graphics.hpp
        src/gui/Screen.hpp
        src/input/Input.cpp
        src/input/Input.hpp
        src/world/WorldState.cpp
        src/world/WorldState.hpp
        src/util/math/Math.cpp
        src/util/math/Math.hpp
        src/world/chunk/Chunk.cpp
        src/world/chunk/Chunk.hpp
        src/world/chunk/ChunkLoader.cpp
        src/world/chunk/ChunkLoader.hpp
        src/physics/Physics.cpp
        src/physics/Physics.hpp
        src/graphics/models/ui/Crosshair.cpp
        src/graphics/models/ui/Crosshair.hpp
        src/graphics/models/skybox/Skybox.cpp
        src/graphics/models/skybox/Skybox.hpp
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
