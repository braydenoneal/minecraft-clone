#pragma once

#include <glm/glm.hpp>

class WorldState {
public:
    glm::vec3 camera_position {3, 3, 3};
    glm::vec3 camera_angle {glm::radians(-45.0f), glm::radians(45.0f), 0};
    float camera_speed{0.1};
};
