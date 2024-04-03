#pragma once

#include <glm/glm.hpp>

class WorldState {
public:
    glm::vec3 camera_position{0, 16, 0};
    glm::vec3 previous_camera_position{camera_position};
    glm::vec3 camera_angle {glm::radians(-90.0f), glm::radians(0.0f), 0};
    float camera_speed{0.25};
};
