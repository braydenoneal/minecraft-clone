#pragma once

#include <array>
#include <vector>
#include <map>

namespace cube {
    static int chunk_size = 16;
    static int chunk_height = 128;
    static int sea_level = 64;

    std::vector<float>
    get_block(bool nx, bool px, bool ny, bool py, bool nz, bool pz, bool nx_ny, bool nx_py, bool px_ny, bool px_py,
              bool nx_nz, bool nx_pz, bool px_nz, bool px_pz, bool ny_nz, bool ny_pz, bool py_nz, bool py_pz,
              bool nx_ny_nz, bool nx_ny_pz, bool nx_py_nz, bool nx_py_pz, bool px_ny_nz, bool px_ny_pz, bool px_py_nz,
              bool px_py_pz) {
        std::vector<float> block_mesh = {};

        /*
         nx
             ny_nz : nx
             ny_pz : nx
             py_nz : nx
             py_pz : nx
         px
             ny_nz : px
             ny_pz : px
             py_nz : px
             py_pz : px
         ny
             nx_nz : ny
             nx_pz : ny
             px_nz : ny
             px_pz : ny
         py
             nx_nz : py
             nx_pz : py
             px_nz : py
             px_pz : py
         nz
             nx_ny : nz
             nx_py : nz
             px_ny : nz
             px_py : nz
         pz
             nx_ny : pz
             nx_py : pz
             px_ny : pz
             px_py : pz
         */

        /*
         -0.5f, -0.5f, -0.5f : (nx_ny || nx_nz || ny_nz || nx_ny_nz) ? 0.f :
         -0.5f, -0.5f, +0.5f : (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.f :
         -0.5f, +0.5f, -0.5f : (nx_py || nx_nz || py_nz || nx_py_nz) ? 0.f :
         -0.5f, +0.5f, +0.5f : (nx_py || nx_pz || py_pz || nx_py_pz) ? 0.f :
         +0.5f, -0.5f, -0.5f : (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.f :
         +0.5f, -0.5f, +0.5f : (px_ny || px_pz || ny_pz || px_ny_pz) ? 0.f :
         +0.5f, +0.5f, -0.5f : (px_py || px_nz || py_nz || px_py_nz) ? 0.f :
         +0.5f, +0.5f, +0.5f : (px_py || px_pz || py_pz || px_py_pz) ? 0.f :
         */

        std::vector<std::vector<float>> meshes = {
                {
                        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, (nx_ny || nx_nz || ny_nz || nx_ny_nz) ? 0.8f : 0.5f,
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 0.8f : 0.5f,
                        -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.8f : 0.5f,
                        -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, (nx_py || nx_pz || py_pz || nx_py_pz) ? 0.8f : 0.5f,
                        -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.8f : 0.5f,
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 0.8f : 0.5f,
                },
                {
                        +0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, (px_py || px_nz || py_nz || px_py_nz) ? 0.8f : 0.5f,
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.8f : 0.5f,
                        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, (px_py || px_pz || py_pz || px_py_pz) ? 0.8f : 0.5f,
                        +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, (px_ny || px_pz || ny_pz || px_ny_pz) ? 0.8f : 0.5f,
                        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, (px_py || px_pz || py_pz || px_py_pz) ? 0.8f : 0.5f,
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.8f : 0.5f,
                },
                {
                        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 2.0f, (nx_ny || nx_nz || ny_nz || nx_ny_nz) ? 0.4f : 0.1f,
                        -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.4f : 0.1f,
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.4f : 0.1f,
                        +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 2.0f, (px_ny || px_pz || ny_pz || px_ny_pz) ? 0.4f : 0.1f,
                        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.4f : 0.1f,
                        -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.4f : 0.1f,
                },
                {
                        -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, (nx_py || nx_pz || py_pz || nx_py_pz) ? 1.0f : 0.7f,
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 1.0f : 0.7f,
                        +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, (px_py || px_pz || py_pz || px_py_pz) ? 1.0f : 0.7f,
                        +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, (px_py || px_nz || py_nz || px_py_nz) ? 1.0f : 0.7f,
                        +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, (px_py || px_pz || py_pz || px_py_pz) ? 1.0f : 0.7f,
                        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 1.0f : 0.7f,
                },
                {
                        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, (nx_ny || nx_nz || ny_nz || nx_ny_nz) ? 0.6f : 0.3f,
                        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.6f : 0.3f,
                        -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 0.6f : 0.3f,
                        +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, (px_py || px_nz || py_nz || px_py_nz) ? 0.6f : 0.3f,
                        -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, (nx_py || nx_nz || py_nz || nx_py_nz) ? 0.6f : 0.3f,
                        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, (px_ny || px_nz || ny_nz || px_ny_nz) ? 0.6f : 0.3f,
                },
                {
                        +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, (px_ny || px_pz || ny_pz || px_ny_pz) ? 0.6f : 0.3f,
                        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.6f : 0.3f,
                        +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, (px_py || px_pz || py_pz || px_py_pz) ? 0.6f : 0.3f,
                        -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, (nx_py || nx_pz || py_pz || nx_py_pz) ? 0.6f : 0.3f,
                        +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, (px_py || px_pz || py_pz || px_py_pz) ? 0.6f : 0.3f,
                        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, (nx_ny || nx_pz || ny_pz || nx_ny_pz) ? 0.6f : 0.3f,
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
        std::vector<std::vector<std::vector<float>>> block_types(chunk_size + 2,
                                                                 std::vector<std::vector<float>>(chunk_height,
                                                                                                 std::vector<float>(
                                                                                                         chunk_size +
                                                                                                         2)));

        for (int x = 0; x < chunk_size + 2; x++) {
            for (int z = 0; z < chunk_size + 2; z++) {
                auto x_position = (float) (x - 1 + chunk_x * chunk_size);
                auto z_position = (float) (z - 1 + chunk_z * chunk_size);

                float y = (float) sea_level + 6 * glm::perlin(glm::vec2(x_position / 16.0f, z_position / 16.0f));

                for (int by = 0; by <= (int) roundf(y); by++) {
                    block_types[x][by][z] = 1.0f;
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

                    bool nx_ny = true;
                    bool nx_py = true;
                    bool px_ny = true;
                    bool px_py = true;
                    bool nx_nz = true;
                    bool nx_pz = true;
                    bool px_nz = true;
                    bool px_pz = true;
                    bool ny_nz = true;
                    bool ny_pz = true;
                    bool py_nz = true;
                    bool py_pz = true;
                    bool nx_ny_nz = true;
                    bool nx_ny_pz = true;
                    bool nx_py_nz = true;
                    bool nx_py_pz = true;
                    bool px_ny_nz = true;
                    bool px_ny_pz = true;
                    bool px_py_nz = true;
                    bool px_py_pz = true;

                    if (y > 0 && y < chunk_height - 1) {
                        // XY
                        nx_ny = block_types[rx - 1][y - 1][rz] == 0.0f;
                        nx_py = block_types[rx - 1][y + 1][rz] == 0.0f;
                        px_ny = block_types[rx + 1][y - 1][rz] == 0.0f;
                        px_py = block_types[rx + 1][y + 1][rz] == 0.0f;

                        // XZ
                        nx_nz = block_types[rx + 1][y][rz - 1] == 0.0f;
                        nx_pz = block_types[rx + 1][y][rz + 1] == 0.0f;
                        px_nz = block_types[rx + 1][y][rz - 1] == 0.0f;
                        px_pz = block_types[rx + 1][y][rz + 1] == 0.0f;

                        // YZ
                        ny_nz = block_types[rx][y - 1][rz - 1] == 0.0f;
                        ny_pz = block_types[rx][y - 1][rz + 1] == 0.0f;
                        py_nz = block_types[rx][y + 1][rz - 1] == 0.0f;
                        py_pz = block_types[rx][y + 1][rz + 1] == 0.0f;

                        // XYZ
                        nx_ny_nz = block_types[rz - 1][y - 1][rz - 1] == 0.0f;
                        nx_ny_pz = block_types[rz - 1][y - 1][rz + 1] == 0.0f;
                        nx_py_nz = block_types[rz - 1][y + 1][rz - 1] == 0.0f;
                        nx_py_pz = block_types[rz - 1][y + 1][rz + 1] == 0.0f;
                        px_ny_nz = block_types[rz + 1][y - 1][rz - 1] == 0.0f;
                        px_ny_pz = block_types[rz + 1][y - 1][rz + 1] == 0.0f;
                        px_py_nz = block_types[rz + 1][y + 1][rz - 1] == 0.0f;
                        px_py_pz = block_types[rz + 1][y + 1][rz + 1] == 0.0f;
                    }

                    if (block_types[x + 1][y][z + 1] > 0.0f) {
                        std::vector<float> block_mesh = get_block(nx, px, ny, py, nz, pz, nx_ny, nx_py, px_ny, px_py,
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
