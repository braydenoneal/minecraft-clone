#pragma once

#include <array>
#include <vector>
#include <map>

namespace cube {
    static int chunk_size = 16;
    static int chunk_height = 128;
    static int sea_level = 64;

    std::vector<float>
    get_block(float block, bool nx, bool px, bool ny, bool py, bool nz, bool pz, bool nx_ny, bool nx_py, bool px_ny, bool px_py,
              bool nx_nz, bool nx_pz, bool px_nz, bool px_pz, bool ny_nz, bool ny_pz, bool py_nz, bool py_pz,
              bool nx_ny_nz, bool nx_ny_pz, bool nx_py_nz, bool nx_py_pz, bool px_ny_nz, bool px_ny_pz, bool px_py_nz,
              bool px_py_pz) {
        std::array<float, 6> face_textures = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

        if (block == 1.0f) {
            face_textures = {0.0f, 0.0f, 2.0f, 1.0f, 0.0f, 0.0f};
        } else if (block == 2.0f) {
            face_textures = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
        } else if (block == 3.0f) {
            face_textures = {3.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f};
        }

        std::vector<float> block_mesh = {};

        std::vector<std::vector<float>> meshes = {
                {
                        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, face_textures[0], 0.8f - (float) ((nx_ny ? 1 : 0) + (nx_nz ? 1 : 0) + (nx_ny_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, face_textures[0], 0.8f - (float) ((nx_py ? 1 : 0) + (nx_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, face_textures[0], 0.8f - (float) ((nx_ny ? 1 : 0) + (nx_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, face_textures[0], 0.8f - (float) ((nx_py ? 1 : 0) + (nx_pz ? 1 : 0) + (nx_py_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, face_textures[0], 0.8f - (float) ((nx_ny ? 1 : 0) + (nx_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, face_textures[0], 0.8f - (float) ((nx_py ? 1 : 0) + (nx_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                },
                {
                        +0.5f, +0.5f, -0.5f, 1.0f, 1.0f, face_textures[1], 0.8f - (float) ((px_py ? 1 : 0) + (px_nz ? 1 : 0) + (px_py_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, face_textures[1], 0.8f - (float) ((px_ny ? 1 : 0) + (px_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, face_textures[1], 0.8f - (float) ((px_py ? 1 : 0) + (px_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, face_textures[1], 0.8f - (float) ((px_ny ? 1 : 0) + (px_pz ? 1 : 0) + (px_ny_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, face_textures[1], 0.8f - (float) ((px_py ? 1 : 0) + (px_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, face_textures[1], 0.8f - (float) ((px_ny ? 1 : 0) + (px_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.8f * 0.5f / 3.0f),
                },
                {
                        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, face_textures[2], 0.4f - (float) ((nx_ny ? 1 : 0) + (ny_nz ? 1 : 0) + (nx_ny_nz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, face_textures[2], 0.4f - (float) ((nx_ny ? 1 : 0) + (ny_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, face_textures[2], 0.4f - (float) ((px_ny ? 1 : 0) + (ny_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                        +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, face_textures[2], 0.4f - (float) ((px_ny ? 1 : 0) + (ny_pz ? 1 : 0) + (px_ny_pz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, face_textures[2], 0.4f - (float) ((px_ny ? 1 : 0) + (ny_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, face_textures[2], 0.4f - (float) ((nx_ny ? 1 : 0) + (ny_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.4f * 0.5f / 3.0f),
                },
                {
                        -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, face_textures[3], 1.0f - (float) ((nx_py ? 1 : 0) + (py_pz ? 1 : 0) + (nx_py_pz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, face_textures[3], 1.0f - (float) ((nx_py ? 1 : 0) + (py_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, face_textures[3], 1.0f - (float) ((px_py ? 1 : 0) + (py_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                        +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, face_textures[3], 1.0f - (float) ((px_py ? 1 : 0) + (py_nz ? 1 : 0) + (px_py_nz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, face_textures[3], 1.0f - (float) ((px_py ? 1 : 0) + (py_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, face_textures[3], 1.0f - (float) ((nx_py ? 1 : 0) + (py_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (1.0f * 0.5f / 3.0f),
                },
                {
                        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, face_textures[4], 0.6f - (float) ((nx_nz ? 1 : 0) + (ny_nz ? 1 : 0) + (nx_ny_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, face_textures[4], 0.6f - (float) ((px_nz ? 1 : 0) + (ny_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, face_textures[4], 0.6f - (float) ((nx_nz ? 1 : 0) + (py_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, face_textures[4], 0.6f - (float) ((px_nz ? 1 : 0) + (py_nz ? 1 : 0) + (px_py_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, face_textures[4], 0.6f - (float) ((nx_nz ? 1 : 0) + (py_nz ? 1 : 0) + (nx_py_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, face_textures[4], 0.6f - (float) ((px_nz ? 1 : 0) + (ny_nz ? 1 : 0) + (px_ny_nz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                },
                {
                        +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, face_textures[5], 0.6f - (float) ((px_pz ? 1 : 0) + (ny_pz ? 1 : 0) + (px_ny_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, face_textures[5], 0.6f - (float) ((nx_pz ? 1 : 0) + (ny_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, face_textures[5], 0.6f - (float) ((px_pz ? 1 : 0) + (py_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, face_textures[5], 0.6f - (float) ((nx_pz ? 1 : 0) + (py_pz ? 1 : 0) + (nx_py_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, face_textures[5], 0.6f - (float) ((px_pz ? 1 : 0) + (py_pz ? 1 : 0) + (px_py_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
                        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, face_textures[5], 0.6f - (float) ((nx_pz ? 1 : 0) + (ny_pz ? 1 : 0) + (nx_ny_pz ? 1 : 0)) * (0.6f * 0.5f / 3.0f),
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
        std::vector<std::vector<std::vector<float>>> block_types(chunk_size + 2, std::vector<std::vector<float>>(chunk_height, std::vector<float>(chunk_size + 2)));

        for (int x = 0; x < chunk_size + 2; x++) {
            for (int z = 0; z < chunk_size + 2; z++) {
                auto x_position = (float) (x - 1 + chunk_x * chunk_size);
                auto z_position = (float) (z - 1 + chunk_z * chunk_size);

                float vertical_scale = 32;
                float horizontal_scale = 24;
                float y = (float) sea_level + vertical_scale * glm::perlin(glm::vec2(x_position / horizontal_scale, z_position / horizontal_scale));

                int grass_height = (int) roundf(y);
                int stone_top_height = grass_height - 2;

                block_types[x][grass_height][z] = 1.0f;

                for (int by = grass_height - 1; by > stone_top_height; by--) {
                    block_types[x][by][z] = 2.0f;
                }

                for (int by = stone_top_height; by >= 0; by--) {
//                    if (std::abs(glm::perlin(glm::vec3(x_position / 16, (float) by / 16, z_position / 16))) < 0.35f)
                    block_types[x][by][z] = 3.0f;
                }
            }
        }

        return block_types;
    }

    std::vector<float>
    block_types_to_mesh(const std::vector<std::vector<std::vector<float>>> &block_types, int chunk_x, int chunk_z) {
        std::vector<float> all_mesh = {};

        for (int x = 0; x < chunk_size; x++) {
            for (int y = 0; y < chunk_height; y++) {
                for (int z = 0; z < chunk_size; z++) {
                    float block = block_types[x + 1][y][z + 1];

                    if (block > 0.0f) {
                        bool nx = block_types[x + 0][y][z + 1] == 0.0f;
                        bool px = block_types[x + 2][y][z + 1] == 0.0f;
                        bool ny = true;
                        bool py = true;
                        if (y > 0) {
                            ny = block_types[x + 1][y - 1][z + 1] == 0.0f;
                        }
                        if (y < chunk_height - 1) {
                            py = block_types[x + 1][y + 1][z + 1] == 0.0f;
                        }
                        bool nz = block_types[x + 1][y][z + 0] == 0.0f;
                        bool pz = block_types[x + 1][y][z + 2] == 0.0f;

                        int rx = x + 1;
                        int rz = z + 1;

                        bool nx_ny = false;
                        bool nx_py = false;
                        bool px_ny = false;
                        bool px_py = false;
                        bool nx_nz = false;
                        bool nx_pz = false;
                        bool px_nz = false;
                        bool px_pz = false;
                        bool ny_nz = false;
                        bool ny_pz = false;
                        bool py_nz = false;
                        bool py_pz = false;
                        bool nx_ny_nz = false;
                        bool nx_ny_pz = false;
                        bool nx_py_nz = false;
                        bool nx_py_pz = false;
                        bool px_ny_nz = false;
                        bool px_ny_pz = false;
                        bool px_py_nz = false;
                        bool px_py_pz = false;

                        if (y > 0 && y < chunk_height - 1) {
                            // XY
                            nx_ny = block_types[rx - 1][y - 1][rz] != 0.0f;
                            nx_py = block_types[rx - 1][y + 1][rz] != 0.0f;
                            px_ny = block_types[rx + 1][y - 1][rz] != 0.0f;
                            px_py = block_types[rx + 1][y + 1][rz] != 0.0f;

                            // XZ
                            nx_nz = block_types[rx - 1][y][rz - 1] != 0.0f;
                            nx_pz = block_types[rx - 1][y][rz + 1] != 0.0f;
                            px_nz = block_types[rx + 1][y][rz - 1] != 0.0f;
                            px_pz = block_types[rx + 1][y][rz + 1] != 0.0f;

                            // YZ
                            ny_nz = block_types[rx][y - 1][rz - 1] != 0.0f;
                            ny_pz = block_types[rx][y - 1][rz + 1] != 0.0f;
                            py_nz = block_types[rx][y + 1][rz - 1] != 0.0f;
                            py_pz = block_types[rx][y + 1][rz + 1] != 0.0f;

                            // XYZ
                            nx_ny_nz = block_types[rx - 1][y - 1][rz - 1] != 0.0f;
                            nx_ny_pz = block_types[rx - 1][y - 1][rz + 1] != 0.0f;
                            nx_py_nz = block_types[rx - 1][y + 1][rz - 1] != 0.0f;
                            nx_py_pz = block_types[rx - 1][y + 1][rz + 1] != 0.0f;
                            px_ny_nz = block_types[rx + 1][y - 1][rz - 1] != 0.0f;
                            px_ny_pz = block_types[rx + 1][y - 1][rz + 1] != 0.0f;
                            px_py_nz = block_types[rx + 1][y + 1][rz - 1] != 0.0f;
                            px_py_pz = block_types[rx + 1][y + 1][rz + 1] != 0.0f;
                        }

                        std::vector<float> block_mesh = get_block(block, nx, px, ny, py, nz, pz, nx_ny, nx_py, px_ny, px_py,
                                                                  nx_nz, nx_pz, px_nz, px_pz, ny_nz, ny_pz, py_nz,
                                                                  py_pz, nx_ny_nz, nx_ny_pz, nx_py_nz, nx_py_pz,
                                                                  px_ny_nz, px_ny_pz, px_py_nz, px_py_pz);

                        block_mesh = position_mesh(block_mesh, (float) (x + 1 + chunk_x * chunk_size), (float) (y),
                                                   (float) (z + 1 + chunk_z * chunk_size));

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

            chunk_locations_to_buffer_data[chunk_location] = block_types_to_mesh(block_types, chunk_location[0],
                                                                                 chunk_location[1]);
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
