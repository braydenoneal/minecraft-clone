#pragma once

#include "../../world/chunk/Chunk.hpp"
#include "../../world/chunk/ChunkLoader.hpp"

class Collision {
public:
    Collision(ChunkLoader &chunk_loader_reference);

    Block getBlockAtPosition(glm::vec3 position);

    bool canMoveTo(glm::vec3 position);

    static bool intersects(glm::vec3 a_min, glm::vec3 a_max,
                           glm::vec3 b_min, glm::vec3 b_max);

private:
    ChunkLoader &chunk_loader;
};
