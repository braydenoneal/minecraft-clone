#include "Input.hpp"

Input::Input(Window &window_reference, WorldState &world_state_reference)
        : window(window_reference), world_state(world_state_reference) {
    glfwSetKeyCallback(window.getGlfwWindow(), key_callback);
    glfwSetFramebufferSizeCallback(window.getGlfwWindow(), resize_callback);
    glfwSetMouseButtonCallback(window.getGlfwWindow(), mouse_button_callback);
    glfwSetScrollCallback(window.getGlfwWindow(), scroll_callback);

    glfwSetWindowUserPointer(window.getGlfwWindow(), this);
}

void Input::pollEvents() {
    glfwPollEvents();

    double current_x;
    double current_y;

    glfwGetCursorPos(window.getGlfwWindow(), &current_x, &current_y);

    cursor_difference_x = current_x - cursor_x;
    cursor_difference_y = current_y - cursor_y;

    cursor_x = current_x;
    cursor_y = current_y;

    float mouse_scale = std::pow(0.5f * 0.6f + 0.2f, 3.0f) * 0.008f;

    world_state.camera_angle.x -= (float) cursor_difference_y * mouse_scale;
    world_state.camera_angle.y -= (float) cursor_difference_x * mouse_scale;

    world_state.camera_angle.x = std::clamp(world_state.camera_angle.x, -(float) M_PI / 2.0f,
                                            (float) M_PI / 2.0f);
    if (world_state.camera_angle.y < -(float) M_PI) {
        world_state.camera_angle.y += (float) M_PI * 2;
    } else if (world_state.camera_angle.y >= (float) M_PI) {
        world_state.camera_angle.y -= (float) M_PI * 2;
    }
}

void Input::key_callback(GLFWwindow *glfw_window, int key, [[maybe_unused]] int scancode, int action,
                         [[maybe_unused]] int mods) {
    auto &input = *(Input *) glfwGetWindowUserPointer(glfw_window);

    input.keys[key] = action;

    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_F11:
                input.window.toggleMaximize();
                break;
            case GLFW_KEY_Q:
                input.window.close();
                break;
            default:
                break;
        }
    }
}

void Input::resize_callback(GLFWwindow *glfw_window, int width, int height) {
    auto &input = *(Input *) glfwGetWindowUserPointer(glfw_window);

    if (width > 0 && height > 0) {
        Graphics::resizeViewport(width, height);
        input.window.setSize(width, height);
    }
}

void Input::mouse_button_callback(GLFWwindow *glfw_window, int button, int action, int mods) {}

void Input::scroll_callback(GLFWwindow *glfw_window, double x_offset, double y_offset) {}
