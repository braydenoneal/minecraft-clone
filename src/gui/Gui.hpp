#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <vector>

class Gui {
public:
    static void create(GLFWwindow *glfw_window);

    static void newFrame();

    static void render();
};
