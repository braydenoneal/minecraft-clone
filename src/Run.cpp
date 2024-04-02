#include <thread>

#include "window/Window.hpp"
#include "graphics/Graphics.hpp"
#include "world/WorldState.hpp"
#include "input/Input.hpp"
#include "gui/Gui.hpp"
#include "gui/screens/DebugScreen.hpp"
#include "graphics/models/cube/Cube.hpp"
#include "world/chunk/ChunkLoader.hpp"

int main() {
    std::mutex mesh_lock{};
    Window window{mesh_lock};
    Graphics graphics{};
    Gui::create(window.getGlfwWindow());
    DebugScreen debug_screen{};
    WorldState world_state{};
    Input input{window, world_state};
    std::vector<offset> mesh{};
    Cube cube{};
    ChunkLoader chunk_loader{world_state, mesh_lock, mesh};

    std::thread chunk_thread(&ChunkLoader::chunkLoop, &chunk_loader);
    chunk_thread.detach();

    while (!window.shouldClose()) {
        input.pollEvents();

        graphics.clearScreen();

        std::unique_lock<std::mutex> unique_mesh_lock(mesh_lock, std::try_to_lock);
        if (unique_mesh_lock) {
            cube.setMesh(mesh);
        }

        cube.cube_array.bind();
        cube.setUniforms(window.getAspectRatio(), world_state.camera_position, world_state.camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        Gui::newFrame();
        debug_screen.render();
        Gui::render();

        window.swapBuffers();
    }

    return 0;
}
