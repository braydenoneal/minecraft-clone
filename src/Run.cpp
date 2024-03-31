#include "window/Window.hpp"
#include "graphics/Graphics.hpp"
#include "world/WorldState.hpp"
#include "input/Input.hpp"
#include "gui/Gui.hpp"
#include "gui/screens/DebugScreen.hpp"
#include "graphics/models/cube/Cube.hpp"

int main() {
    Window window{};
    Graphics graphics{};
    Gui::create(window.getGlfwWindow());
    DebugScreen debug_screen{};
    WorldState world_state{};
    Input input{window, world_state};
    Cube cube{};

    int r = 0;
    int x = -r;
    int ry = 0;
    int y = -ry;
    int z = -r;
    int d = 0;

    while (!window.shouldClose()) {
        input.pollEvents();

        graphics.clearScreen();

        cube.cube_array.bind();

        cube.renderChunk(x, y, z);

        y++;

        if (y >= ry) {
            y = -ry;

            if (d == 0) {
                x++;

                if (x >= r) {
                    d = 1;
                }
            } else if (d == 1) {
                z++;

                if (z >= r) {
                    d = 2;
                }
            } else if (d == 2) {
                x--;

                if (x <= -r) {
                    d = 3;
                }
            } else {
                z--;

                if (z <= -r) {
                    d = 0;
                    r++;
                    x = -r;
                    z = -r;
                }
            }
        }

        cube.setUniforms(window.getAspectRatio(), world_state.camera_position, world_state.camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        Gui::newFrame();
        debug_screen.render();
        Gui::render();

        window.swapBuffers();
    }

    return 0;
}
