#include "Window.hpp"

Window::Window() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    glfw_window = glfwCreateWindow(1920, 1080, "Minecraft", nullptr, nullptr);

    glfwMakeContextCurrent(glfw_window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    glfwSwapInterval(1);

    glfwGetWindowSize(glfw_window, &width, &height);
}

Window::~Window() {
    glfwTerminate();
}

void Window::swapBuffers() {
    glfwSwapBuffers(glfw_window);
    glfwPollEvents();
}

int Window::shouldClose() {
    return glfwWindowShouldClose(glfw_window);
}

void Window::close() {
    glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
}

GLFWwindow *Window::getGlfwWindow() {
    return glfw_window;
}

float Window::getAspectRatio() const {
    return (float) width / (float) height;
}
