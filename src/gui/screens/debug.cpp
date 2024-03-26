#include "debug.hpp"

namespace debug {
    void render() {
        ImGui::Begin("Debug");
        ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
