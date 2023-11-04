#include <array>
#include <random>

class Chunk {
public:
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

    static std::array<float, 210 * 16 * 16> flat_chunk_positions() {
        std::array<float, 210 * 16 * 16> positions{};

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 16);

        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                std::array<float, 210> block_positions = cube_positions_at((float) x, (float) dist6(rng), (float) z);

                for (int i = 0; i < 210; i++) {
                    positions[x * 210 * 16 + z * 210 + i] = block_positions[i];
                }
            }
        }

        return positions;
    }

    static std::array<unsigned int, 36 * 16 * 16> flat_chunk_indices() {
        std::array<unsigned int, 36 * 16 * 16> indices{};

        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                std::array<unsigned int, 36> block_indices = cube_indices();

                for (int i = 0; i < 36; i++) {
                    indices[x * 36 * 16 + z * 36 + i] = block_indices[i] + x * 30 * 16 + z * 30;

                }
            }
        }

        return indices;
    }
};
