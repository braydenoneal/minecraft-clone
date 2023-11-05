#include <array>
#include <random>
#include <glm/gtc/noise.hpp>

struct BlockFaces {
    unsigned int block;
    unsigned int x;
    unsigned int y;
    unsigned int z;
    bool positive_x;
    bool negative_x;
    bool positive_y;
    bool negative_y;
    bool positive_z;
    bool negative_z;
};

struct Vertex {
    float x;
    float y;
    float z;
    float s;
    float t;
    float texture;
    float brightness;
};

struct Face {
    Vertex vertex0;
    Vertex vertex1;
    Vertex vertex2;
    Vertex vertex3;
    Vertex vertex4;
};

class Chunk {
public:
    static std::array<std::array<std::array<unsigned int, 16>, 16>, 16> flat_chunk_blocks() {
        std::array<std::array<std::array<unsigned int, 16>, 16>, 16> blocks{};

        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                blocks[x][0][z] = 1;
            }
        }

        return blocks;
    }

    static std::array<std::array<std::array<BlockFaces, 16>, 16>, 16> get_block_faces(std::array<std::array<std::array<unsigned int, 16>, 16>, 16> chunk_blocks) {
        std::array<std::array<std::array<BlockFaces, 16>, 16>, 16> block_faces{};

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    bool positive_x = true;
                    if (x < 15 && chunk_blocks[x + 1][y][z] > 0) {
                        positive_x = false;
                    }
                    bool negative_x = true;
                    if (x > 0 && chunk_blocks[x - 1][y][z] > 0) {
                        positive_x = false;
                    }
                    bool positive_y = true;
                    if (y < 15 && chunk_blocks[x][y + 1][z] > 0) {
                        positive_y = false;
                    }
                    bool negative_y = true;
                    if (y > 0 && chunk_blocks[x][y - 1][z] > 0) {
                        positive_y = false;
                    }
                    bool positive_z = true;
                    if (z < 15 && chunk_blocks[x][y][z + 1] > 0) {
                        positive_z = false;
                    }
                    bool negative_z = true;
                    if (z > 0 && chunk_blocks[x][y][z - 1] > 0) {
                        positive_z = false;
                    }

                    block_faces[x][y][z] = {
                            chunk_blocks[x][y][z], (unsigned int) x, (unsigned int) y, (unsigned int) z,
                            positive_x, negative_x, positive_y, negative_y, positive_z, negative_z
                    };
                }
            }
        }
    }

    static Face get_positive_x_face() {
        return {
                { 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f },
                { 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f },
                { 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f },
                { 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f },
                { 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f },
        };
    }

    static Face get_negative_x_face() {
        return {
                { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.8f },
                { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.8f },
                { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f },
                { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f },
                { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f },
        };
    }

    static Face get_positive_y_face() {
        return {
                { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f },
                { -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f },
                {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f },
                {  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f },
                {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f },
        };
    }

    static Face get_negative_y_face() {
        return {
                {  0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  2.0f,  0.4f },
                {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  2.0f,  0.4f },
                { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f },
                { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  2.0f,  0.4f },
                { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f },
        };
    }

    static Face get_positive_z_face() {
        return {
                {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f },
                {  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.6f },
                { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f },
                { -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f },
                { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f },
        };
    }

    static Face get_negative_z_face() {
        return {
                { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.6f },
                { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.6f },
                {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f },
                {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f },
                {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f },
        };
    }

    static std::array<std::array<std::array<float, 7>, 5>, 6> cube_vertices() {
        std::array<std::array<std::array<float, 7>, 5>, 6> vertices = {
                std::array<std::array<float, 7>, 5> {  // -Z
                    std::array<float, 7> { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.6f, },
                    std::array<float, 7> { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.6f, },
                    std::array<float, 7> {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f, },
                    std::array<float, 7> {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f, },
                    std::array<float, 7> {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f, },
                },
                std::array<std::array<float, 7>, 5> {  // +Z
                    std::array<float, 7> {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f, },
                    std::array<float, 7> {  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.6f, },
                    std::array<float, 7> { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f, },
                    std::array<float, 7> { -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f, },
                    std::array<float, 7> { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f, },
                },
                std::array<std::array<float, 7>, 5> {  // -X
                    std::array<float, 7> { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.8f, },
                    std::array<float, 7> { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.8f, },
                    std::array<float, 7> { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f, },
                    std::array<float, 7> { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f, },
                    std::array<float, 7> { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f, },
                },
                std::array<std::array<float, 7>, 5> {  // +X
                    std::array<float, 7> {  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f, },
                    std::array<float, 7> {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f, },
                    std::array<float, 7> {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f, },
                    std::array<float, 7> {  0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f, },
                    std::array<float, 7> {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f, },
                },
                std::array<std::array<float, 7>, 5> {  // +Y
                    std::array<float, 7> { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f, },
                    std::array<float, 7> { -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f, },
                    std::array<float, 7> {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f, },
                    std::array<float, 7> {  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f, },
                    std::array<float, 7> {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f, },
                },
                std::array<std::array<float, 7>, 5> {  // -Y
                    std::array<float, 7> {  0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  2.0f,  0.4f, },
                    std::array<float, 7> {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  2.0f,  0.4f, },
                    std::array<float, 7> { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f, },
                    std::array<float, 7> { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  2.0f,  0.4f, },
                    std::array<float, 7> { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f, },
                },
        };

        return vertices;
    }

    static std::array<std::array<std::array<std::array<std::array<std::array<float, 7>, 5>, 6>, 16>, 16>, 16> chunk_vertices(std::array<std::array<std::array<BlockFaces, 16>, 16>, 16> chunk_faces) {
        std::array<std::array<std::array<std::array<std::array<std::array<float, 7>, 5>, 6>, 16>, 16>, 16> vertices{};
        std::array<std::array<std::array<float, 7>, 5>, 6> default_cube_vertices = cube_vertices();

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    BlockFaces block_faces = chunk_faces[x][y][z];

                    if (block_faces.positive_x) {
                        vertices[x][y][z][3] = default_cube_vertices[3];
                    }
                    if (block_faces.negative_x) {
                        vertices[x][y][z][2] = default_cube_vertices[2];
                    }
                    if (block_faces.positive_y) {
                        vertices[x][y][z][4] = default_cube_vertices[4];
                    }
                    if (block_faces.negative_y) {
                        vertices[x][y][z][5] = default_cube_vertices[5];
                    }
                    if (block_faces.positive_z) {
                        vertices[x][y][z][1] = default_cube_vertices[1];
                    }
                    if (block_faces.negative_z) {
                        vertices[x][y][z][0] = default_cube_vertices[0];
                    }
                }
            }
        }

        return vertices;
    }

    static std::list<std::array<std::array<float, 7>, 5>> mutable_vertices(std::array<std::array<std::array<std::array<std::array<std::array<float, 7>, 5>, 6>, 16>, 16>, 16> chunk_vertices) {
        std::list<std::array<std::array<float, 7>, 5>> vertices{};
        std::list<std::array<unsigned int, 6>> indices{};

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    for (int face = 0; face < 6; face++) {
                        if (!chunk_vertices[x][y][z][face].empty()) {
                            vertices.push_back(chunk_vertices[x][y][z][face]);
                        }
                    }
                }
            }
        }

        return vertices;
    }

    static std::list<Face> get_chunk_vertices(std::array<std::array<std::array<BlockFaces, 16>, 16>, 16> chunk_faces) {
        std::list<Face> vertices{};

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    BlockFaces block_faces = chunk_faces[x][y][z];

                    if (block_faces.positive_x) {
                        vertices.push_back(get_positive_x_face());
                    }
                    if (block_faces.negative_x) {
                        vertices.push_back(get_negative_x_face());
                    }
                    if (block_faces.positive_y) {
                        vertices.push_back(get_positive_y_face());
                    }
                    if (block_faces.negative_y) {
                        vertices.push_back(get_negative_y_face());
                    }
                    if (block_faces.positive_z) {
                        vertices.push_back(get_positive_z_face());
                    }
                    if (block_faces.negative_z) {
                        vertices.push_back(get_negative_z_face());
                    }
                }
            }
        }

        return vertices;
    }

    static const unsigned int size = 16;

    static std::array<float, 210> cube_positions() {
        std::array<float, 210> positions = {
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.6f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.6f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f,
             0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f,

             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.6f,
            -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f,
            -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f,
            -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f,

            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.8f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.8f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f,
            -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f,
            -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f,

             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f,

            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f,

             0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  2.0f,  0.4f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  2.0f,  0.4f,
            -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f,
            -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  2.0f,  0.4f,
            -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f,
        };

        return positions;
    }

    static std::array<unsigned int, 36> cube_indices() {
        std::array<unsigned int, 36> indices = {
                0, 1, 2, 3, 4, 1,
                5, 6, 7, 8, 9, 6,
                10, 11, 12, 13, 14, 11,
                15, 16, 17, 18, 19, 16,
                20, 21, 22, 23, 24, 21,
                25, 26, 27, 28, 29, 26
        };

        return indices;
    }

    static std::array<float, 210> cube_positions_at(float x, float y, float z) {
        std::array<float, 210> positions = cube_positions();

        for (int row = 0; row < 30; row++) {
            positions[row * 7 + 0] += x;
            positions[row * 7 + 1] += y;
            positions[row * 7 + 2] += z;
        }

        return positions;
    }

    static std::array<float, 210 * size * size> flat_chunk_positions() {
        std::array<float, 210 * size * size> positions{};

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
//                std::array<float, 210> block_positions = cube_positions_at((float) x, roundf(size / 4 * glm::simplex(glm::vec2((float) x / size, (float) z / size))), (float) z);
                std::array<float, 210> block_positions = cube_positions_at((float) x, 0, (float) z);

                for (int i = 0; i < 210; i++) {
                    positions[x * 210 * size + z * 210 + i] = block_positions[i];
                }
            }
        }

        return positions;
    }

    static std::array<float, 210 * size * size> flat_chunk_positions(int chunk_x, int chunk_z) {
        std::array<float, 210 * size * size> positions{};

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                std::array<float, 210> block_positions = cube_positions_at((float) x, roundf(size / 4 * glm::perlin(glm::vec2((float) (x + chunk_x * Chunk::size) / size, (float) (z + chunk_z * Chunk::size) / size))), (float) z);

                for (int i = 0; i < 210; i++) {
                    positions[x * 210 * size + z * 210 + i] = block_positions[i];
                }
            }
        }

        return positions;
    }

    static std::array<unsigned int, 36 * size * size> flat_chunk_indices() {
        std::array<unsigned int, 36 * size * size> indices{};

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                std::array<unsigned int, 36> block_indices = cube_indices();

                for (int i = 0; i < 36; i++) {
                    indices[x * 36 * size + z * 36 + i] = block_indices[i] + x * 30 * size + z * 30;

                }
            }
        }

        return indices;
    }
};
