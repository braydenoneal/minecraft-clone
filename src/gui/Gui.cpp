#include "Gui.hpp"

void Gui::create(GLFWwindow *glfw_window) {
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGui::StyleColorsDark();
}

void Gui::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
}

void Gui::render() {
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
