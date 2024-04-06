#pragma once

#include "../../world/chunk/Chunk.hpp"
#include "../../world/chunk/ChunkLoader.hpp"

class Collision {
public:
    explicit Collision(ChunkLoader &chunk_loader_reference);

    Block getBlockAtPosition(glm::vec3 position);

    glm::vec3 canMoveTo(glm::vec3 start_position, glm::vec3 end_position);

private:
    ChunkLoader &chunk_loader;

    static bool intersect(glm::vec3 plane_point, glm::vec3 plane_normal, glm::vec3 ray_point, glm::vec3 ray_direction,
                          glm::vec3 &intersection_point);

    static glm::vec3 moveTo(glm::vec3 start_position, glm::vec3 end_position, glm::vec3 cube_position);
};
