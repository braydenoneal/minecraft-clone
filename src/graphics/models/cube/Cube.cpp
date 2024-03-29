#include "Cube.hpp"

Cube::Cube() {
    shader.setShaders("../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
    shader.bind();

    texture.setTextures({"../res/textures/grass_block_side.png"}, 16, 16);
    texture.bind();

    shader.setUniform1i("u_textures", 0);

    struct offset {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLint f;
    };

    vector<offset> offset_data = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 2},
        {0, 0, 0, 3},
        {0, 0, 0, 4},
        {0, 0, 0, 5},
    };

    instance_count = (GLsizei) offset_data.size();

    VertexBuffer offset_buffer{};
    offset_buffer.setData((GLsizeiptr) (offset_data.size() * sizeof(offset)), &offset_data[0]);

    struct vertex {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat u;
        GLfloat v;
        GLfloat t;
    };

    vector<vertex> vertex_buffer_data = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1, 0},
        {0, 0, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 0},
    };

    triangle_count = (GLsizei) vertex_buffer_data.size();

    VertexBuffer cube_buffer{};
    cube_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(vertex)), &vertex_buffer_data[0]);

    cube_array.addAttributes(cube_buffer, {{3, GL_FLOAT, GL_FALSE}, {3, GL_FLOAT, GL_FALSE}}, 0);
    cube_array.addAttributes(offset_buffer, {{3, GL_FLOAT, GL_FALSE}, {1, GL_INT, GL_FALSE}}, 1);
}

void Cube::set_uniforms() const {
    glm::mat4 perspective = glm::perspective(
        glm::radians(70.0f),
        (float) 1920 / (float) 1080,
        0.05f, 2048.0f
    );

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, 1 * glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, 1 * glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, 0 * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f), -glm::vec3(3, 3, 3));
    glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
}
