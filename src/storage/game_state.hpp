#pragma once

namespace game_state {
    static float camera_height = 2.125f;
    static glm::vec3 camera_position{glm::vec3(0.0f, camera_height, -5.0f)};
    static glm::vec3 camera_angle{glm::vec3(0.0f, 0.0f, 0.0f)};
    static float camera_speed = 0.05f;

    static bool jumping = false;
    static int jump_counter = 0;
}
