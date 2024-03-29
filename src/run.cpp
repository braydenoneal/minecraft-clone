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
        glDrawArraysInstanced(GL_TRIANGLES, 0, 12, 100);

        cube.set_uniforms();

        gui::new_frame();
        debug::render();
        gui::render();

        window::next_frame(glfw_window);
    }

    window::terminate();

    return 0;
}
