#include <map>
#include <algorithm>

#include "window/window.hpp"
#include "graphics/render/render.hpp"
#include "gui/gui.hpp"
#include "gui/screens/debug.hpp"
#include "graphics/models/cube/Cube.hpp"

double cursor_x = 0.0;
double cursor_y = 0.0;
double cursor_difference_x = 0.0;
double cursor_difference_y = 0.0;
std::map<int, int> keys;

glm::vec3 translate_in_direction_by_amount(glm::vec3 position, float angle, glm::vec3 amount) {
    glm::mat4 rotate_mat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 rotated_amount = rotate_mat * glm::vec4(amount, 1.0f);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), rotated_amount);
    return translation * glm::vec4(position, 1.0f);
}

void key_callback(GLFWwindow *glfw_window, int key, int scancode, int action, int mods) {
    keys[key] = action;

    if (action == GLFW_PRESS && key == GLFW_KEY_Q) {
        window::close(glfw_window);
    }
}

int main() {
    GLFWwindow *glfw_window = window::create_context();
    render::create_context();
    gui::create_context(glfw_window);

    glfwSetKeyCallback(glfw_window, key_callback);

    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    glm::vec3 camera_position = {3, 3, 3};
    glm::vec3 camera_angle = {
        1 * glm::radians(-45.0f),
        1 * glm::radians(45.0f),
        0 * glm::radians(45.0f),
    };

    Cube cube{};

    while (!window::should_close(glfw_window)) {
        render::clear_screen();

        double current_x;
        double current_y;
        glfwGetCursorPos(glfw_window, &current_x, &current_y);

        cursor_difference_x = current_x - cursor_x;
        cursor_difference_y = current_y - cursor_y;

        cursor_x = current_x;
        cursor_y = current_y;

        float mouse_scale = std::pow(0.5f * 0.6f + 0.2f, 3.0f) * 0.008f;

        camera_angle.x -= (float) cursor_difference_y * mouse_scale;
        camera_angle.y -= (float) cursor_difference_x * mouse_scale;

        camera_angle.x = std::clamp(camera_angle.x, -(float) M_PI / 2.0f, (float) M_PI / 2.0f);

        if (camera_angle.y < -(float) M_PI) {
            camera_angle.y += (float) M_PI * 2;
        } else if (camera_angle.y >= (float) M_PI) {
            camera_angle.y -= (float) M_PI * 2;
        }

        for (std::pair<const int, int> key: keys) {
            if (key.second) {
                switch (key.first) {
                    case GLFW_KEY_W:
                        camera_position = translate_in_direction_by_amount(
                                camera_position, camera_angle.y,
                                glm::vec3(0.0f, 0.0f, -0.1f));
                        break;
                    case GLFW_KEY_A:
                        camera_position = translate_in_direction_by_amount(
                                camera_position, camera_angle.y,
                                glm::vec3(-0.1f, 0.0f, 0.0f));
                        break;
                    case GLFW_KEY_S:
                        camera_position = translate_in_direction_by_amount(
                                camera_position, camera_angle.y,
                                glm::vec3(0.0f, 0.0f, 0.1f));
                        break;
                    case GLFW_KEY_D:
                        camera_position = translate_in_direction_by_amount(
                                camera_position, camera_angle.y,
                                glm::vec3(0.1f, 0.0f, 0.0f));
                        break;
                    case GLFW_KEY_SPACE:
                        camera_position.y += 0.1f;
                        break;
                    case GLFW_KEY_LEFT_SHIFT:
                        camera_position.y -= 0.1f;
                        break;
                    default:
                        break;
                }
            }
        }

        cube.cube_array.bind();
        cube.set_uniforms(camera_position, camera_angle);
        glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, cube.triangle_count, cube.instance_count);

        gui::new_frame();
        debug::render();
        gui::render();

        window::next_frame(glfw_window);
    }

    window::terminate();

    return 0;
}
