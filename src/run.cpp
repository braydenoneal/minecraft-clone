#include "window/window.hpp"
#include "graphics/render/render.hpp"
#include "gui/gui.hpp"
#include "gui/screens/debug.hpp"
#include "graphics/models/cube/Cube.hpp"

int main() {
    GLFWwindow *glfw_window = window::create_context();
    render::create_context();
    gui::create_context(glfw_window);

    Cube cube{};

    while (!window::should_close(glfw_window)) {
        render::clear_screen();

        cube.cube_array.bind();
        cube.set_uniforms();
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        gui::new_frame();
        debug::render();
        gui::render();

        window::next_frame(glfw_window);
    }

    window::terminate();

    return 0;
}
