#pragma once

#include <cmath>
#include <algorithm>

#include "../math/math.hpp"

namespace input {
    void get_input() {
        glfwPollEvents();

        double current_x;
        double current_y;
        glfwGetCursorPos(input_state::glfw_window, &current_x, &current_y);

        input_state::cursor_difference_x = current_x - input_state::cursor_x;
        input_state::cursor_difference_y = current_y - input_state::cursor_y;

        input_state::cursor_x = current_x;
        input_state::cursor_y = current_y;
    }

    void update_game_state() {
        if (!input_state::paused) {
            // TODO: This is from Minecraft
            float mouse_scale = std::pow(user_state::mouse_sensitivity * 0.6f + 0.2f, 3.0f) * 0.008f;

            game_state::camera_angle.x -= (float) input_state::cursor_difference_y * mouse_scale;
            game_state::camera_angle.y -= (float) input_state::cursor_difference_x * mouse_scale;

            game_state::camera_angle.x = std::clamp(game_state::camera_angle.x, -(float) M_PI / 2.0f,
                                                    (float) M_PI / 2.0f);
            if (game_state::camera_angle.y < -(float) M_PI) {
                game_state::camera_angle.y += (float) M_PI * 2;
            } else if (game_state::camera_angle.y >= (float) M_PI) {
                game_state::camera_angle.y -= (float) M_PI * 2;
            }

            for (std::pair<const int, int> key: input_state::keys) {
                if (key.second) {
                    switch (key.first) {
                        case GLFW_KEY_W:
                            window::move_camera(math::translate_in_direction_by_amount(
                                    game_state::camera_position, game_state::camera_angle.y,
                                    glm::vec3(0.0f, 0.0f, -game_state::camera_speed)));
                            break;
                        case GLFW_KEY_A:
                            window::move_camera(math::translate_in_direction_by_amount(
                                    game_state::camera_position, game_state::camera_angle.y,
                                    glm::vec3(-game_state::camera_speed, 0.0f, 0.0f)));
                            break;
                        case GLFW_KEY_S:
                            window::move_camera(math::translate_in_direction_by_amount(
                                    game_state::camera_position, game_state::camera_angle.y,
                                    glm::vec3(0.0f, 0.0f, game_state::camera_speed)));
                            break;
                        case GLFW_KEY_D:
                            window::move_camera(math::translate_in_direction_by_amount(
                                    game_state::camera_position, game_state::camera_angle.y,
                                    glm::vec3(game_state::camera_speed, 0.0f, 0.0f)));
                            break;
                        case GLFW_KEY_SPACE:
                            if (window::air_time == 0) {
                                window::jumping = true;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }

    void key_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods) {
        input_state::keys[key] = action;

        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_F11:
                    window::toggle_maximize();
                    break;
                case GLFW_KEY_ESCAPE:
                case GLFW_KEY_E:
                    window::toggle_pause();
                    break;
                case GLFW_KEY_Q:
                    window::close();
                    break;
                case GLFW_KEY_TAB:
                    game_state::camera_speed += 2.0f;
                    break;
                case GLFW_KEY_C:
                    user_state::field_of_view = 30.0f;
                    user_state::mouse_sensitivity /= 2.0f;
                    break;
                case GLFW_KEY_1:
                    window::selected_block = 1;
                    break;
                case GLFW_KEY_2:
                    window::selected_block = 2;
                    break;
                case GLFW_KEY_3:
                    window::selected_block = 3;
                    break;
                case GLFW_KEY_4:
                    window::selected_block = 4;
                    break;
                default:
                    break;
            }
        } else if (action == GLFW_RELEASE) {
            switch (key) {
                case GLFW_KEY_TAB:
                    game_state::camera_speed -= 2.0f;
                    break;
                case GLFW_KEY_C:
                    user_state::field_of_view = 70.0f;
                    user_state::mouse_sensitivity *= 2.0f;
                    break;
                default:
                    break;
            }
        }
    }

    void resize_callback(GLFWwindow *glfw_window, int width, int height) {
        if (width > 0 && height > 0) {
            glViewport(0, 0, width, height);
            input_state::window_width = width;
            input_state::window_height = height;
        }
    }

    void mouse_button_callback(GLFWwindow *glfw_window, int button, int action, int mods) {
        ImGui_ImplGlfw_MouseButtonCallback(glfw_window, button, action, mods);

        if (!input_state::paused && action == GLFW_PRESS) {
            switch (button) {
                case (GLFW_MOUSE_BUTTON_RIGHT):
                    window::place_block(window::selected_block);
                    break;
                case (GLFW_MOUSE_BUTTON_LEFT):
                    window::place_block(0);
                    break;
                default:
                    break;
            }
        }
    }

    void scroll_callback(GLFWwindow* glfw_window, double x_offset, double y_offset) {
        if (y_offset > 0) {
            window::selected_block -= 1;
            if (window::selected_block < 1) {
                window::selected_block = 4;
            }
        } else {
            window::selected_block += 1;
            if (window::selected_block > 4) {
                window::selected_block = 1;
            }
        }
    }

    void create_context() {
        glfwSetKeyCallback(input_state::glfw_window, key_callback);
        glfwSetFramebufferSizeCallback(input_state::glfw_window, resize_callback);
        glfwSetMouseButtonCallback(input_state::glfw_window, mouse_button_callback);
        glfwSetScrollCallback(input_state::glfw_window, scroll_callback);
    }
}
