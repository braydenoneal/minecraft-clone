#include <thread>

#include "window/Window.hpp"
#include "graphics/Graphics.hpp"
#include "world/WorldState.hpp"
#include "input/Input.hpp"
#include "gui/Gui.hpp"
#include "gui/screens/DebugScreen.hpp"
#include "graphics/models/cube/Cube.hpp"
#include "world/chunk/ChunkLoader.hpp"
#include "physics/Physics.hpp"
#include "graphics/models/ui/Crosshair.hpp"
#include "graphics/models/skybox/Skybox.hpp"

int main() {
    Window window{};
    Graphics graphics{};
    Gui::create(window.getGlfwWindow());
    DebugScreen debug_screen{};
    WorldState world_state{};
    Input input{window, world_state};
    Physics physics{input, world_state};

    std::thread update_thread(&Physics::updateLoop, &physics);
    update_thread.detach();

    Cube cube{};

    std::mutex mesh_lock{};
    std::vector<offset> mesh{};
    ChunkLoader chunk_loader{world_state, mesh_lock, mesh};

    std::thread chunk_thread(&ChunkLoader::chunkLoop, &chunk_loader);
    chunk_thread.detach();

    Skybox skybox{};
    Crosshair crosshair{};

    while (!window.shouldClose()) {
        input.pollEvents();

        graphics.clearScreen();

        physics.processMovement();

        {
            std::unique_lock<std::mutex> unique_mesh_lock(mesh_lock, std::try_to_lock);

            if (unique_mesh_lock) {
                cube.setMesh(mesh);
            }
        }

        glDisable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);

        skybox.shader.bind();
        skybox.vertex_array.bind();
        skybox.setUniforms(window.getAspectRatio(), world_state.camera_angle);
        skybox.draw();
        VertexArray::unbind();
        Shader::unbind();

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        cube.shader.bind();
        cube.cube_array.bind();
        cube.setUniforms(window.getAspectRatio(), world_state.camera_position, world_state.camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);
        VertexArray::unbind();
        Shader::unbind();

        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);

        crosshair.shader.bind();
        crosshair.vertex_array.bind();
        crosshair.setUniforms(window.getAspectRatio(), (float) window.getWidth());
        crosshair.draw();
        VertexArray::unbind();
        Shader::unbind();

        Gui::newFrame();
        debug_screen.render();
        Gui::render();

        window.swapBuffers();
    }

    return 0;
}
