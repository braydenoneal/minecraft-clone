#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace window {
    void create_context();

    void clear_screen();

    void next_frame();

    int should_close();

    void close();

    void terminate();
}
