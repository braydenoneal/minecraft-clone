#include "DebugScreen.hpp"

void DebugScreen::render() {
//    float current_framerate = ImGui::GetIO().Framerate;
//
//    if (past_frame_rates.size() > 300) {
//        for (int i = 0; i < past_frame_rates.size(); i++) {
//            past_frame_rates[i - 1] = past_frame_rates[i];
//        }
//        past_frame_rates[past_frame_rates.size() - 1] = current_framerate;
//    } else {
//        past_frame_rates.push_back(current_framerate);
//    }

    ImGui::Begin("Debug");
    ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
//    ImGui::PlotHistogram("", &past_frame_rates[0], (int) past_frame_rates.size(), 0, nullptr, 0.0f, 10.0f,
//                         ImVec2(300, 100));
    ImGui::End();
}
