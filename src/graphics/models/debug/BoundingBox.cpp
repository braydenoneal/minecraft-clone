#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
    shader.setShaders("../res/shaders/debug/bounding_box/vertex.glsl",
                      "../res/shaders/debug/bounding_box/fragment.glsl");
    shader.bind();

    std::vector<BoundingBoxVertex> vertex_buffer_data = {
            {-0.29f, -1.59f, -0.29f},
            {-0.29f, -1.59f, +0.29f},

            {+0.29f, -1.59f, -0.29f},
            {+0.29f, -1.59f, +0.29f},

            {-0.29f, -1.59f, +0.29f},
            {+0.29f, -1.59f, +0.29f},

            {-0.29f, -1.59f, -0.29f},
            {+0.29f, -1.59f, -0.29f},

            {-0.29f, +0.19f, -0.29f},
            {-0.29f, +0.19f, +0.29f},

            {+0.29f, +0.19f, -0.29f},
            {+0.29f, +0.19f, +0.29f},

            {-0.29f, +0.19f, +0.29f},
            {+0.29f, +0.19f, +0.29f},

            {-0.29f, +0.19f, -0.29f},
            {+0.29f, +0.19f, -0.29f},

            {-0.29f, -1.59f, -0.29f},
            {-0.29f, +0.19f, -0.29f},

            {-0.29f, -1.59f, +0.29f},
            {-0.29f, +0.19f, +0.29f},

            {+0.29f, -1.59f, -0.29f},
            {+0.29f, +0.19f, -0.29f},

            {+0.29f, -1.59f, +0.29f},
            {+0.29f, +0.19f, +0.29f},
    };

    vertex_count = (GLsizei) vertex_buffer_data.size();

    vertex_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(BoundingBoxVertex)), &vertex_buffer_data[0]);

    vertex_array.addAttributes(vertex_buffer, {{3, GL_FLOAT, GL_FALSE}}, 0);
}

void BoundingBox::draw() const {
    glDrawArrays(GL_LINES, 0, vertex_count);
}

void BoundingBox::setUniforms(float aspect_ratio, glm::vec3 camera_angle) const {
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), aspect_ratio, 0.05f, 2048.0f);

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, -camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_matrix = perspective * camera_rotate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
}
