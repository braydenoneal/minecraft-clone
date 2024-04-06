#pragma once

#include <imgui.h>
#include <vector>

#include "../Screen.hpp"

class DebugScreen {
public:
    void render();

private:
    std::vector<float> past_frame_rates{};
};
