#include "Skybox.hpp"


Skybox::Skybox() {
    shader.setShaders("../res/shaders/skybox/vertex.glsl", "../res/shaders/skybox/fragment.glsl");
    shader.bind();

    std::vector<SkyboxVertex> vertex_buffer_data = {
        {-1, 0, -1},
        {-1, 0, +1},
        {+1, 0, -1},
        {+1, 0, +1},
        {+1, 0, -1},
        {-1, 0, +1},
    };

    vertex_count = (GLsizei) vertex_buffer_data.size();

    vertex_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(SkyboxVertex)), &vertex_buffer_data[0]);

    vertex_array.addAttributes(vertex_buffer, {{3, GL_FLOAT, GL_FALSE}}, 0);
}

void Skybox::draw() const {
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Skybox::setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) const {
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), aspect_ratio, 0.05f, 2048.0f);

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, -camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_matrix = perspective * camera_rotate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
    shader.setUniform4fv("u_position", &camera_position[0]);
}
