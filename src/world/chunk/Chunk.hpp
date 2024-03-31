#pragma once

#include <glm/gtc/noise.hpp>
#include <vector>

#define CHUNK_SIZE 16

struct Block {
    int id;
};

struct Position {
    int x;
    int y;
    int z;
};

class Chunk {
public:
    Position position{};
    std::vector<Block> blocks{CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE};

    explicit Chunk(Position chunk_position);

    [[nodiscard]] Block get(int block_x, int block_y, int block_z) const;

    void set(int block_x, int block_y, int block_z, Block block);
};
