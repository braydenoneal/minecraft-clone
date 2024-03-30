#include "window/window.hpp"
#include "graphics/render/render.hpp"
#include "gui/gui.hpp"
#include "gui/screens/debug.hpp"
#include "graphics/models/cube/Cube.hpp"

int main() {
    GLFWwindow *glfw_window = window::create_context();
    render::create_context();
    gui::create_context(glfw_window);

    glm::vec3 camera_position = {3, 3, 3};
    glm::vec3 camera_angle = {glm::radians(-45.0f), glm::radians(45.0f), 0};

    Cube cube{};

    while (!window::should_close(glfw_window)) {
        render::clear_screen();

        cube.cube_array.bind();
        cube.set_uniforms(camera_position, camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        gui::new_frame();
        debug::render();
        gui::render();

        window::next_frame(glfw_window);
    }

    window::terminate();

    return 0;
}
