#include "DebugScreen.hpp"

void DebugScreen::render() const {
    ImGui::Begin("Debug");
    ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
    ImGui::End();
}
