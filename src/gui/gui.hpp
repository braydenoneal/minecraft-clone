#include "GLFW/glfw3.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace gui {
    void create_context(GLFWwindow *window);

    void new_frame();

    void render();
}
