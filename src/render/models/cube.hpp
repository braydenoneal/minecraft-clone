#pragma once

#include <array>
#include <vector>
#include <map>

namespace cube {
    static int chunk_size = 16;

    std::array<float, 7 * 6 * 6> get_buffer_data() {
        return {
                // Left -X
                -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                -0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                // Right +X
                +0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                // Bottom -Y
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 2.0f, 0.4f,
                -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                // Top +Y
                -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                // Front -Z
                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                // Back +Z
                +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
        };
    }

    std::array<float, 7 * 6 * 6> get_buffer_data_at_position(glm::vec3 position) {
        std::array<float, 7 * 6 * 6> buffer_data = get_buffer_data();

        for (int vertex = 0; vertex < buffer_data.size(); vertex += 7) {
            buffer_data[vertex] += position.x;
            buffer_data[vertex + 1] += position.y;
            buffer_data[vertex + 2] += position.z;
        }

        return buffer_data;
    }

    std::vector<float> get_buffer_data_at_positions(const std::vector<glm::vec3> &positions) {
        std::vector<float> buffer_data = {};

        for (glm::vec3 position: positions) {
            std::array<float, 7 * 6 * 6> position_buffer_data = get_buffer_data_at_position(position);

            for (float value: position_buffer_data) {
                buffer_data.push_back(value);
            }
        }

        return buffer_data;
    }

    std::vector<float> get_chunk_buffer_data_at_position(int chunk_x, int chunk_z) {
        std::vector<glm::vec3> positions = {};

        for (int x = 0; x < chunk_size; x++) {
            for (int z = 0; z < chunk_size; z++) {
                auto x_position = (float) (x + chunk_x * chunk_size);
                auto z_position = (float) (z + chunk_z * chunk_size);

                float y = 6 * glm::perlin(glm::vec2(x_position / 16.0f, z_position / 16.0f));

                positions.emplace_back(x_position, roundf(y), z_position);
            }
        }

        return cube::get_buffer_data_at_positions(positions);
    }

    std::vector<float> get_chunk_buffer_data_combined(const std::vector<std::vector<float>> &chunk_buffer_datas) {
        std::vector<float> buffer_data = {};

        for (const std::vector<float> &chunk_buffer_data: chunk_buffer_datas) {
            for (float value: chunk_buffer_data) {
                buffer_data.push_back(value);
            }
        }

        return buffer_data;
    }

    std::map<std::array<int, 2>, std::vector<float>>
    chunk_locations_to_buffer_data(const std::vector<std::array<int, 2>> &chunk_locations) {
        std::map<std::array<int, 2>, std::vector<float>> chunk_locations_to_buffer_data = {};

        for (std::array<int, 2> chunk_location: chunk_locations) {
            chunk_locations_to_buffer_data[chunk_location] =
                    get_chunk_buffer_data_at_position(chunk_location[0], chunk_location[1]);
        }

        return chunk_locations_to_buffer_data;
    }

    std::vector<float>
    combine_chunks(const std::map<std::array<int, 2>, std::vector<float>> &chunk_locations_to_buffer_data) {
        std::vector<float> buffer_data = {};

        for (const auto &[key, value]: chunk_locations_to_buffer_data) {
            for (float val: value) {
                buffer_data.push_back(val);
            }
        }

        return buffer_data;
    }
}
