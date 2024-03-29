#include "window/window.hpp"
#include "graphics/render/render.hpp"
#include "gui/gui.hpp"
#include "gui/screens/debug.hpp"

#include "graphics/models/cube/cube.hpp"

int main() {
    GLFWwindow *glfw_window = window::create_context();
    render::create_context();
    gui::create_context(glfw_window);

    cube::render_context cube_context = cube::create_context();

    while (!window::should_close(glfw_window)) {
        render::clear_screen();

//        vertex_buffer::render(6);
        vertex_array::bind(cube_context.vertex_array_id);
        glDrawArraysInstanced(GL_TRIANGLES, 0, 12, 100);

        cube::set_uniforms(cube_context);

        gui::new_frame();
        debug::render();
        gui::render();

        window::next_frame(glfw_window);
    }

    window::terminate();

    return 0;
}
