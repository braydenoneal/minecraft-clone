#pragma once

#include <imgui.h>

#include "../Screen.hpp"

class DebugScreen: public Screen {
public:
    void render() const override;
};
