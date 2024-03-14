#pragma once

#include <map>

namespace input_state {
    static bool maximized = true;
    static bool paused = false;
    static int window_width = 1920;
    static int window_height = 1080;
    static double cursor_x = 0.0;
    static double cursor_y = 0.0;
    static double cursor_difference_x = 0.0;
    static double cursor_difference_y = 0.0;
    static GLFWwindow *glfw_window;
    static std::map<int, int> keys;
}
