#include "window.hpp"

namespace window {
    GLFWwindow *glfw_window;

    void create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfw_window = glfwCreateWindow(640, 480, "Minecraft", nullptr, nullptr);

        glfwMakeContextCurrent(glfw_window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);

        glfwWindowHint(GLFW_SAMPLES, 4);
    }

    void next_frame() {
        glfwSwapBuffers(glfw_window);
    }

    int should_close() {
        return glfwWindowShouldClose(glfw_window);
    }

    void close() {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
    }

    void terminate() {
        glfwTerminate();
    }
}
