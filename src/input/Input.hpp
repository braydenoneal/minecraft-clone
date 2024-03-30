#pragma once

#include <map>
#include <cmath>
#include <algorithm>

#include "../window/Window.hpp"
#include "../world/WorldState.hpp"
#include "../util/math/Math.hpp"
#include "../graphics/Graphics.hpp"

class Input {
public:
    explicit Input(Window &window_reference, WorldState &world_state_reference);

    void pollEvents();

private:
    Window &window;
    WorldState &world_state;
    std::map<int, int> keys{};
    double cursor_x = 0.0;
    double cursor_y = 0.0;
    double cursor_difference_x = 0.0;
    double cursor_difference_y = 0.0;

    static void key_callback(GLFWwindow *glfw_window, int key, [[maybe_unused]] int scancode, int action, int mods);

    static void resize_callback(GLFWwindow *glfw_window, int width, int height);

    static void mouse_button_callback(GLFWwindow *glfw_window, int button, int action, int mods);

    static void scroll_callback(GLFWwindow* glfw_window, double x_offset, double y_offset);
};
