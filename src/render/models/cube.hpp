#pragma once

#include <array>
#include <vector>

namespace cube {
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
}
