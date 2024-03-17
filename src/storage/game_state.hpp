#pragma once

namespace game_state {
    static glm::vec3 camera_position{glm::vec3(8.5f, 96.0f, 8.5f)};
    static glm::vec3 camera_angle{glm::vec3(-(float) M_PI / 2, 0.0f, 0.0f)};
    static float camera_speed = 0.05f;
    static const int chunk_size = 16;
    static const int chunk_height = 64;
    static const int sea_level = 32;
}
