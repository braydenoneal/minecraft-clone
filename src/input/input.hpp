#pragma once

#include <map>
#include <iostream>

#include "../window/window.hpp"

namespace input {
    static std::map<int, int> keys;

    void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
        keys[key] = action;

        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_F11:
                    window::toggle_maximize();
                    break;
                case GLFW_KEY_Q:
                    window::close();
                    break;
                default:
                    break;
            }
        }
    }

    void poll_events() {
        glfwPollEvents();
        double current_x;
        double current_y;
        glfwGetCursorPos(window::get_glfw_window(), &current_x, &current_y);
        window::cursor_difference_x = current_x - window::cursor_x;
        window::cursor_difference_y = current_y - window::cursor_y;
        window::cursor_x = current_x;
        window::cursor_y = current_y;

        matter::camera_angle.y += (float) window::cursor_difference_x / ((float) M_PI * 200.0f);
        matter::camera_angle.x += (float) window::cursor_difference_y / ((float) M_PI * 200.0f);

        for (std::pair<const int, int> key : keys) {
            if (key.second) {
                switch (key.first) {
                    case GLFW_KEY_A:
                        matter::camera_position.x -= matter::camera_speed;
                        break;
                    case GLFW_KEY_D:
                        matter::camera_position.x += matter::camera_speed;
                        break;
                    case GLFW_KEY_SPACE:
                        matter::camera_position.y += matter::camera_speed;
                        break;
                    case GLFW_KEY_LEFT_SHIFT:
                        matter::camera_position.y -= matter::camera_speed;
                        break;
                    case GLFW_KEY_S:
                        matter::camera_position.z -= matter::camera_speed;
                        break;
                    case GLFW_KEY_W:
                        matter::camera_position.z += matter::camera_speed;
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void resize_callback(GLFWwindow* window, int width, int height) {
        if (width > 0 && height > 0) {
            glViewport(0, 0, width, height);
            window::width = width;
            window::height = height;
        }
    }

    void create_context() {
        glfwSetKeyCallback(window::get_glfw_window(), key_callback);
        glfwSetFramebufferSizeCallback(window::get_glfw_window(), resize_callback);
    }
}
