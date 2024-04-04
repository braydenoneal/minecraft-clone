#include "Chunk.hpp"

bool Position::operator==(const Position &position) const {
    return x == position.x && y == position.y && z == position.z;
}

Chunk::Chunk(Position chunk_position) {
    position = chunk_position;

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            auto x_position = (float) (x + position.x * CHUNK_SIZE);
            auto z_position = (float) (z + position.z * CHUNK_SIZE);

            float vertical_scale = 15;
            float horizontal_scale = 24;
            float noise_value = glm::perlin(glm::vec2(x_position / horizontal_scale, z_position / horizontal_scale));
            float surface_y = vertical_scale + vertical_scale * noise_value - (float) (chunk_position.y * CHUNK_SIZE);

            for (int y = 0; y <= (int) std::round(surface_y) && y < CHUNK_SIZE; y++) {
                set(x, y, z, {1});
            }
        }
    }
}

Block Chunk::get(int block_x, int block_y, int block_z) const {
    return blocks[block_x * CHUNK_SIZE * CHUNK_SIZE + block_y * CHUNK_SIZE + block_z];
}

void Chunk::set(int block_x, int block_y, int block_z, Block block) {
    blocks[block_x * CHUNK_SIZE * CHUNK_SIZE + block_y * CHUNK_SIZE + block_z] = block;
}
