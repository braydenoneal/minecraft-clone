#include "window.hpp"

namespace window {
    GLFWwindow *create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *glfw_window = glfwCreateWindow(1920, 1080, "Minecraft", nullptr, nullptr);

        glfwMakeContextCurrent(glfw_window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);

        return glfw_window;
    }

    void next_frame(GLFWwindow *glfw_window) {
        glfwSwapBuffers(glfw_window);
        glfwPollEvents();
    }

    int should_close(GLFWwindow *glfw_window) {
        return glfwWindowShouldClose(glfw_window);
    }

    void close(GLFWwindow *glfw_window) {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
    }

    void terminate() {
        glfwTerminate();
    }
}
