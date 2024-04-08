#pragma once

#include <glm/glm.hpp>

#include "../../world/chunk/Chunk.hpp"
#include "../../world/chunk/ChunkLoader.hpp"
#include "../../graphics/models/entity/pig/Pig.hpp"

class PigPhysics {
public:
    glm::vec3 position{0, 16, 0};
    glm::vec3 rotation{0, 0, 0};
    ChunkLoader &chunk_loader;
    Pig &pig;
    int max_travel_distance = 16;
    glm::vec3 current_destination{getRandomDestination()};
    bool jumping = false;

    float pig_rotation = 0;
    float pig_rotation_direction = 1;
    int pig_counter = 0;
    glm::vec3 previous_pig_position = position;
    glm::vec3 pos_int = {0, 0, 0};
    glm::vec3 previous_pig_rotation = rotation;
    glm::vec3 rot_int = {0, 0, 0};
    int rot_counter = 0;
    int anim_time = 100;

    explicit PigPhysics(ChunkLoader &chunk_loader, Pig &pig);

    [[nodiscard]] glm::vec3 getRandomDestination() const;

    [[nodiscard]] glm::vec3 getNextBlockPosition();

    void stepAnimation(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle);
};
