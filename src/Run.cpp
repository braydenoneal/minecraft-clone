#include <thread>
#include <iostream>

#include "window/Window.hpp"
#include "graphics/Graphics.hpp"
#include "world/WorldState.hpp"
#include "input/Input.hpp"
#include "gui/Gui.hpp"
#include "gui/screens/DebugScreen.hpp"
#include "graphics/models/cube/Cube.hpp"
#include "world/chunk/ChunkLoader.hpp"
#include "physics/Physics.hpp"
#include "physics/collision/Collision.hpp"
#include "graphics/models/ui/Crosshair.hpp"
#include "graphics/models/skybox/Skybox.hpp"
#include "graphics/models/debug/BoundingBox.hpp"
#include "graphics/models/entity/pig/Pig.hpp"

int main() {
    Window window{};
    Graphics graphics{};
    Gui::create(window.getGlfwWindow());
    DebugScreen debug_screen{};
    WorldState world_state{};
    Input input{window, world_state};

    Cube cube{};

    std::mutex mesh_lock{};
    std::vector<offset> mesh{};
    ChunkLoader chunk_loader{mesh_lock, mesh, world_state.camera_position};

    std::thread chunk_thread(&ChunkLoader::chunkLoop, &chunk_loader);
    chunk_thread.detach();

    Collision collision{chunk_loader};
    std::mutex physics_lock{};
    Physics physics{input, world_state, collision, physics_lock};

    std::thread update_thread(&Physics::updateLoop, &physics);
    update_thread.detach();

    Skybox skybox{};
    Crosshair crosshair{};
    bool render_bounding_box = false;
    BoundingBox bounding_box{};
    Pig pig{};

    while (!window.shouldClose()) {
        input.pollEvents();

        graphics.clearScreen();

        physics_lock.lock();
        physics.processMovement();
        physics_lock.unlock();

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
        cube.texture.bind();
        cube.setUniforms(window.getAspectRatio(), world_state.camera_position, world_state.camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);
        Texture::unbind();
        VertexArray::unbind();
        Shader::unbind();

        pig.shader.bind();
        pig.vertex_array.bind();
        pig.texture.bind();
        pig.setUniforms(window.getAspectRatio(), world_state.camera_position, world_state.camera_angle);
        pig.draw();
        Texture::unbind();
        VertexArray::unbind();
        Shader::unbind();

        if (render_bounding_box) {
            glLineWidth(4);

            bounding_box.shader.bind();
            bounding_box.vertex_array.bind();
            bounding_box.setUniforms(window.getAspectRatio(), world_state.camera_angle);
            bounding_box.draw();
            VertexArray::unbind();
            Shader::unbind();
        }

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
