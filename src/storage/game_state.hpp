#pragma once

namespace game_state {
    static glm::vec3 camera_position{glm::vec3(8.5f, 163.6f, 8.5f)};
    static glm::vec3 camera_angle{glm::vec3(0.0f, 0.0f, 0.0f)};
    static float camera_speed = 0.05f;
    static const int chunk_size = 16;
    static const int chunk_height = 128;
    static const int sea_level = 64;
}
