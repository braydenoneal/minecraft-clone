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

    void updateLoop();

    glm::vec3 getIntermediatePosition();

private:
    Input &input;
    WorldState &world_state;
    steady_clock::time_point last_update;
    int update_frequency_microseconds = (int) (1e6 / 60.0f);
    float previous_time_factor{0};
    bool moving = false;
};
