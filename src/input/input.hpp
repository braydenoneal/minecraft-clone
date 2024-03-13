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

    glm::vec3 translate_in_direction_by_amount(glm::vec3 position, float angle, glm::vec3 amount) {
        glm::mat4 rotate_mat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 rotated_amount = rotate_mat * glm::vec4(amount, 1.0f);
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), rotated_amount);
        return translation * glm::vec4(position, 1.0f);
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

        matter::camera_angle.x += (float) window::cursor_difference_y / ((float) M_PI * 200.0f);
        matter::camera_angle.y += (float) window::cursor_difference_x / ((float) M_PI * 200.0f);

        matter::camera_angle.x = std::max(-(float) M_PI / 2.0f, matter::camera_angle.x);
        matter::camera_angle.x = std::min( (float) M_PI / 2.0f, matter::camera_angle.x);

        for (std::pair<const int, int> key : keys) {
            if (key.second) {
                switch (key.first) {
                    case GLFW_KEY_A:
                        matter::camera_position = translate_in_direction_by_amount(
                            matter::camera_position, matter::camera_angle.y,
                            glm::vec3(-matter::camera_speed, 0.0f, 0.0f)
                        );
                        break;
                    case GLFW_KEY_D:
                        matter::camera_position = translate_in_direction_by_amount(
                            matter::camera_position, matter::camera_angle.y,
                            glm::vec3(matter::camera_speed, 0.0f, 0.0f)
                        );
                        break;
                    case GLFW_KEY_SPACE:
                        matter::camera_position.y += matter::camera_speed;
                        break;
                    case GLFW_KEY_LEFT_SHIFT:
                        matter::camera_position.y -= matter::camera_speed;
                        break;
                    case GLFW_KEY_S:
                        matter::camera_position = translate_in_direction_by_amount(
                            matter::camera_position, matter::camera_angle.y,
                            glm::vec3(0.0f, 0.0f, -matter::camera_speed)
                        );
                        break;
                    case GLFW_KEY_W:
                        matter::camera_position = translate_in_direction_by_amount(
                            matter::camera_position, matter::camera_angle.y,
                            glm::vec3(0.0f, 0.0f, matter::camera_speed)
                        );
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
