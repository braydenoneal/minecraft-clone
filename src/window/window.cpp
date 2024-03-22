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
    }

    void clear_screen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(166.0f / 255.0f, 208.0f / 255.0f, 1.0f, 1.0f);
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
