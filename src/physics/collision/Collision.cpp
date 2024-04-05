#include "Collision.hpp"

Collision::Collision(ChunkLoader &chunk_loader_reference) : chunk_loader(chunk_loader_reference) {}

Block Collision::getBlockAtPosition(glm::vec3 position) {
    int chunk_x = std::floor(position.x / (float) CHUNK_SIZE);
    int chunk_y = std::floor(position.y / (float) CHUNK_SIZE);
    int chunk_z = std::floor(position.z / (float) CHUNK_SIZE);

    for (const auto &chunk: chunk_loader.chunks) {
        if (chunk_x == chunk.position.x && chunk_y == chunk.position.y && chunk_z == chunk.position.z) {
            int x = (int) std::floor(position.x) % CHUNK_SIZE;
            int y = (int) std::floor(position.y) % CHUNK_SIZE;
            int z = (int) std::floor(position.z) % CHUNK_SIZE;

            return chunk.get(x, y, z);
        }
    }

    return {0};
}

bool Collision::canMoveTo(glm::vec3 position) {
    glm::vec3 player_min = {position.x - 0.3f, position.y - 1.6f, position.z - 0.3f};
    glm::vec3 player_max = {position.x + 0.3f, position.y + 0.2f, position.z + 0.3f};

    bool can_move = true;

    for (int x = (int) std::floor(player_min.x); x < (int) std::ceil(player_max.x); x++) {
        for (int y = (int) std::floor(player_min.y); y < (int) std::ceil(player_max.y); y++) {
            for (int z = (int) std::floor(player_min.z); z < (int) std::ceil(player_max.z); z++) {
                if (getBlockAtPosition(glm::vec3((float) x, (float) y, (float) z)).id != 0) {
                    glm::vec3 block_min = {x, y, z};
                    glm::vec3 block_max = {x + 1, y + 1, z + 1};

                    if (!intersects(player_min, player_max, block_min, block_max)) {
                        can_move = false;
                    }
                }
            }
        }
    }

    return can_move;
}

bool Collision::intersects(glm::vec3 a_min, glm::vec3 a_max, glm::vec3 b_min, glm::vec3 b_max) {
    return (a_min.x <= b_max.x && a_max.x >= b_min.x &&
            a_min.y <= b_max.y && a_max.y >= b_min.y &&
            a_min.z <= b_max.z && a_max.z >= b_min.z);
}
