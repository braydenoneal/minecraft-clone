#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Input {
    void create_context() {}

    void poll_events() {
        glfwPollEvents();
    }
}
