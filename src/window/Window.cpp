#include "Window.hpp"

Window::Window(std::mutex &_m_reference) : _m(_m_reference) {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, maximized);

    glfw_window = glfwCreateWindow(1920, 1080, "Minecraft", nullptr, nullptr);

    glfwMakeContextCurrent(glfw_window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(vsync_enabled);

    glfwGetWindowSize(glfw_window, &width, &height);

    glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    glfwSetCursorPos(glfw_window, 0, 0);
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfw_window);
}

int Window::shouldClose() {
    std::lock_guard<std::mutex> lock(_m);
    return glfwWindowShouldClose(glfw_window);
}

void Window::close() {
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

void Window::toggleMaximize() {
    maximized = !maximized;

    if (maximized) {
        glfwMaximizeWindow(glfw_window);
    } else {
        glfwRestoreWindow(glfw_window);
    }

    glfwGetWindowSize(glfw_window, &width, &height);
}

GLFWwindow *Window::getGlfwWindow() {
    return glfw_window;
}

float Window::getAspectRatio() const {
    return (float) width / (float) height;
}

void Window::setSize(int new_width, int new_height) {
    width = new_width;
    height = new_height;
}
