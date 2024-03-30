#include "window/Window.hpp"
#include "graphics/Graphics.hpp"
#include "gui/gui.hpp"
#include "gui/screens/debug.hpp"
#include "graphics/models/cube/Cube.hpp"

int main() {
    Window window{};
    Graphics graphics{};
    gui::create_context(window.getGlfwWindow());

    glm::vec3 camera_position = {3, 3, 3};
    glm::vec3 camera_angle = {glm::radians(-45.0f), glm::radians(45.0f), 0};

    Cube cube{};

    while (!window.shouldClose()) {
        graphics.clearScreen();

        cube.cube_array.bind();
        cube.set_uniforms(window.getAspectRatio(), camera_position, camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        gui::new_frame();
        debug::render();
        gui::render();

        window.swapBuffers();
    }

    return 0;
}
