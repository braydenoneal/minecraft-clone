#pragma once

#include <chrono>
#include <thread>

#include "../input/Input.hpp"
#include "../world/WorldState.hpp"
#include "../util/math/Math.hpp"

using namespace std::chrono;

class Physics {
public:
    Physics(Input &input_reference, WorldState &world_state_reference);

    void processMovement();

    void updateLoop();

private:
    Input &input;
    WorldState &world_state;
    int update_frequency_microseconds = (int) (1e6 / 60.0f);
    steady_clock::time_point last_update;
    float previous_time_factor{0};
    bool moving = false;
};
