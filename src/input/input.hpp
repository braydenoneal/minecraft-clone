#pragma once

namespace input {
    void key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
        input_state::keys[key] = action;

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
        glfwGetCursorPos(input_state::glfw_window, &current_x, &current_y);
        input_state::cursor_difference_x = current_x - input_state::cursor_x;
        input_state::cursor_difference_y = current_y - input_state::cursor_y;
        input_state::cursor_x = current_x;
        input_state::cursor_y = current_y;

        game_state::camera_angle.x += (float) input_state::cursor_difference_y / ((float) M_PI * 200.0f);
        game_state::camera_angle.y += (float) input_state::cursor_difference_x / ((float) M_PI * 200.0f);

        game_state::camera_angle.x = std::max(-(float) M_PI / 2.0f, game_state::camera_angle.x);
        game_state::camera_angle.x = std::min( (float) M_PI / 2.0f, game_state::camera_angle.x);

        for (std::pair<const int, int> key : input_state::keys) {
            if (key.second) {
                switch (key.first) {
                    case GLFW_KEY_A:
                        game_state::camera_position = translate_in_direction_by_amount(
                            game_state::camera_position, game_state::camera_angle.y,
                            glm::vec3(-game_state::camera_speed, 0.0f, 0.0f)
                        );
                        break;
                    case GLFW_KEY_D:
                        game_state::camera_position = translate_in_direction_by_amount(
                            game_state::camera_position, game_state::camera_angle.y,
                            glm::vec3(game_state::camera_speed, 0.0f, 0.0f)
                        );
                        break;
                    case GLFW_KEY_SPACE:
                        if (game_state::camera_position.y == 0.0f) {
                            game_state::jumping = true;
                        }
                        break;
                    case GLFW_KEY_LEFT_SHIFT:
                        game_state::camera_position.y -= game_state::camera_speed;
                        break;
                    case GLFW_KEY_S:
                        game_state::camera_position = translate_in_direction_by_amount(
                            game_state::camera_position, game_state::camera_angle.y,
                            glm::vec3(0.0f, 0.0f, -game_state::camera_speed)
                        );
                        break;
                    case GLFW_KEY_W:
                        game_state::camera_position = translate_in_direction_by_amount(
                            game_state::camera_position, game_state::camera_angle.y,
                            glm::vec3(0.0f, 0.0f, game_state::camera_speed)
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
            input_state::window_width = width;
            input_state::window_height = height;
        }
    }

    void create_context() {
        glfwSetKeyCallback(input_state::glfw_window, key_callback);
        glfwSetFramebufferSizeCallback(input_state::glfw_window, resize_callback);
    }
}
