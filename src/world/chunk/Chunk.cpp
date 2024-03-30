#include "Chunk.hpp"

Block Chunk::get(int block_x, int block_y, int block_z) {
    return blocks[block_x * CHUNK_SIZE * CHUNK_SIZE + block_y * CHUNK_SIZE + block_z];
}
