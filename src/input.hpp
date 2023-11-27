#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace input {
    void create_context() {}

    void poll_events() {
        glfwPollEvents();
    }
}
