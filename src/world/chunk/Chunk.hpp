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
    Block blocks[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE]{};

    Block get(int block_x, int block_y, int block_z);
};
