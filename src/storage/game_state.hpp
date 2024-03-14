#pragma once

namespace game_state {
    static glm::vec3 camera_position{glm::vec3(0.0f, 0.0f, -5.0f)};
    static glm::vec3 camera_angle{glm::vec3(0.0f, 0.0f, 0.0f)};
    static float camera_speed = 0.1f;

    static bool jumping = false;
    static int jump_counter = 0;
}
