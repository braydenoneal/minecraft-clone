class GuiContext {
public:
    static void init(WindowContext window_context) {
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window_context.window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();
    }

    static void render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            ImGui::Begin("Debug");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    static void terminate() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
};
