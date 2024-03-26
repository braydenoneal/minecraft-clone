#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace window {
    GLFWwindow *create_context();

    void next_frame(GLFWwindow *glfw_window);

    int should_close(GLFWwindow *glfw_window);

    void close(GLFWwindow *glfw_window);

    void terminate();
}
