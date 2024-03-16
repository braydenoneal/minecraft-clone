#pragma once

#include <array>
#include <vector>
#include <map>

#include "../../world/chunk/chunk.hpp"

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

    // Chunk location to block data
    chunk::chunk chunk_location_to_block_data(int chunk_x, int chunk_z) {
        chunk::chunk chunk_data = {chunk_x, chunk_z};

        for (int x = 0; x < chunk_size; x++) {
            for (int z = 0; z < chunk_size; z++) {
                auto x_position = (float) (x + chunk_x * chunk_size);
                auto z_position = (float) (z + chunk_z * chunk_size);

                float vertical_scale = 6;
                float horizontal_scale = 16;
                float y = (float) sea_level + vertical_scale * glm::perlin(glm::vec2(x_position / horizontal_scale, z_position / horizontal_scale));

                int grass_height = (int) roundf(y);
                int stone_top_height = grass_height - 2;

                chunk_data.blocks[chunk::pos(x, grass_height, z)] = {1};
//
//                for (int by = grass_height - 1; by >= 0; by--) {
//                    chunk_data.blocks[chunk::pos(x, by, z)] = {3};
//                }
            }
        }

        return chunk_data;
    }

    // Chunk data to mesh
    chunk::chunk_mesh chunk_data_to_mesh(chunk::chunk chunk_data) {
        std::vector<float> mesh = {};

        for (int x = 0; x < chunk_size; x++) {
            for (int y = 0; y < chunk_height; y++) {
                for (int z = 0; z < chunk_size; z++) {
                    auto block = (float) chunk_data.blocks[chunk::pos(x, y, z)].id;

                    if (block != 0) {
                        std::vector<float> block_mesh = get_block(block, true, true, true, true, true, true, false,
                                                                  false,
                                                                  false, false, false, false, false, false, false,
                                                                  false, false,
                                                                  false, false, false, false, false, false, false,
                                                                  false, false);

                        block_mesh = position_mesh(block_mesh, (float) (x + 1 + chunk_data.x * chunk_size), (float) (y),
                                                   (float) (z + 1 + chunk_data.z * chunk_size));

                        for (float value: block_mesh) {
                            mesh.emplace_back(value);
                        }
                    }
                }
            }
        }

        return {chunk_data.x, chunk_data.z, mesh};
    }

    // Chunk datas to mesh
    std::vector<float> chunk_meshes_to_total_mesh(const std::vector<chunk::chunk_mesh> &chunk_meshes) {
        std::vector<float> mesh = {};

        for (chunk::chunk_mesh chunk_mesh: chunk_meshes) {
            mesh.insert(mesh.end(), chunk_mesh.mesh.begin(), chunk_mesh.mesh.end());
        }

        return mesh;
    }
}
