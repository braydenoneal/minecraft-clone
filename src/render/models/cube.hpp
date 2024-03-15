#pragma once

#include <array>
#include <vector>
#include <map>

namespace cube {
    static int chunk_size = 16;
    static int chunk_height = 64;

    std::vector<float> get_block(bool nx, bool px, bool ny, bool py, bool nz, bool pz) {
        std::vector<float> block_mesh = {};

        std::vector<std::vector<float>> meshes = {
                {
                    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                    -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                    -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                    -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                    -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                    -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                },
                {
                    +0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                    +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                    +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                    +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                    +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                },
                {
                    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 2.0f, 0.4f,
                    -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                    +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                    +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 2.0f, 0.4f,
                    +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                    -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                },
                {
                    -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
                    -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                    +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                    +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
                    +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                    -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                },
                {
                    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                    -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                    +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                    -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                    +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                },
                {
                    +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                    +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                    -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                    +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                    -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                }
        };

        if (nx) {
            block_mesh.insert(block_mesh.end(), meshes[0].begin(), meshes[0].end());
        }
        if (px) {
            block_mesh.insert(block_mesh.end(), meshes[1].begin(), meshes[1].end());
        }
        if (ny) {
            block_mesh.insert(block_mesh.end(), meshes[2].begin(), meshes[2].end());
        }
        if (py) {
            block_mesh.insert(block_mesh.end(), meshes[3].begin(), meshes[3].end());
        }
        if (nz) {
            block_mesh.insert(block_mesh.end(), meshes[4].begin(), meshes[4].end());
        }
        if (pz) {
            block_mesh.insert(block_mesh.end(), meshes[5].begin(), meshes[5].end());
        }

        return block_mesh;
    }

    std::vector<float> position_mesh(const std::vector<float> &mesh, float x, float y, float z) {
        std::vector<float> new_mesh = mesh;

        for (int value = 0; value < mesh.size(); value += 7) {
            new_mesh[value] += x;
            new_mesh[value + 1] += y;
            new_mesh[value + 2] += z;
        }

        return new_mesh;
    }

    std::vector<std::vector<std::vector<float>>> chunk_location_to_block_types(int chunk_x, int chunk_z) {
        std::vector<std::vector<std::vector<float>>> block_types(chunk_size, std::vector<std::vector<float>>(chunk_height, std::vector<float>(chunk_size)));

        for (int x = 0; x < chunk_size; x++) {
            for (int z = 0; z < chunk_size; z++) {
                auto x_position = (float) (x + chunk_x * chunk_size);
                auto z_position = (float) (z + chunk_z * chunk_size);

                float y = 6 * (glm::perlin(glm::vec2(x_position / 16.0f, z_position / 16.0f)) + 1);

                for (int by = (int) roundf(y); by >= 0; by--) {
                    block_types[x][by][z] = 1.0f;
                }
            }
        }

        return block_types;
    }

    std::vector<float> block_types_to_mesh(const std::vector<std::vector<std::vector<float>>> &block_types, int chunk_x, int chunk_z) {
        std::vector<float> all_mesh = {};

        for (int x = 0; x < chunk_size; x++) {
            for (int y = 0; y < chunk_height; y++) {
                for (int z = 0; z < chunk_size; z++) {
                    bool nx, px, ny, py, nz, pz = true;

                    if (x > 0) {
                        nx = block_types[x - 1][y][z] == 0.0f;
                    }
                    if (x < chunk_size - 1) {
                        px = block_types[x + 1][y][z] == 0.0f;
                    }
                    if (y > 0) {
                        ny = block_types[x][y - 1][z] == 0.0f;
                    }
                    if (y < chunk_height - 1) {
                        py = block_types[x][y + 1][z] == 0.0f;
                    }
                    if (z > 0) {
                        nz = block_types[x][y][z - 1] == 0.0f;
                    }
                    if (z < chunk_size - 1) {
                        pz = block_types[x][y][z + 1] == 0.0f;
                    }

                    if (block_types[x][y][z] > 0.0f) {
                        std::vector<float> block_mesh = get_block(nx, px, ny, py, nz, pz);

                        block_mesh = position_mesh(block_mesh, (float) (x + chunk_x * chunk_size), (float) (y), (float) (z + chunk_z * chunk_size));

                        for (float value: block_mesh) {
                            all_mesh.emplace_back(value);
                        }
                    }
                }
            }
        }

        return all_mesh;
    }

    std::map<std::array<int, 2>, std::vector<float>>
    chunk_locations_to_buffer_data(const std::vector<std::array<int, 2>> &chunk_locations) {
        std::map<std::array<int, 2>, std::vector<float>> chunk_locations_to_buffer_data = {};

        for (std::array<int, 2> chunk_location: chunk_locations) {
            auto block_types = chunk_location_to_block_types(chunk_location[0], chunk_location[1]);

            chunk_locations_to_buffer_data[chunk_location] = block_types_to_mesh(block_types, chunk_location[0], chunk_location[1]);
        }

        return chunk_locations_to_buffer_data;
    }

    std::vector<float>
    combine_chunks(const std::map<std::array<int, 2>, std::vector<float>> &chunk_locations_to_buffer_data) {
        std::vector<float> buffer_data = {};

        int reserve_space = 0;

        for (const auto &[key, value]: chunk_locations_to_buffer_data) {
            reserve_space += (int) value.size();
        }

        buffer_data.reserve(reserve_space);

        for (const auto &[key, value]: chunk_locations_to_buffer_data) {
            buffer_data.insert(buffer_data.end(), value.begin(), value.end());
        }

        return buffer_data;
    }
}
