#include "cube.hpp"

namespace cube {
    render_context create_context() {
        GLuint shader_id = shader::create("../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
        GLuint texture_id = texture::create(
            {"../res/textures/grass_block_side.png", "../res/textures/grass_block_side.png"}, 16, 16
        );

        GLuint vertex_buffer_id = vertex_buffer::create();
        vertex_buffer::bind(vertex_buffer_id);

        GLuint vertex_array_id = vertex_array::create({
            {3, GL_FLOAT, GL_FALSE},
        });

        vertex_array::bind(vertex_array_id);
        shader::bind(shader_id);
        texture::bind(texture_id);

        struct vertex {
            GLfloat x;
            GLfloat y;
            GLfloat z;
        };

        vector<vertex> vertex_buffer_data = {
            {0, 0, 0},
            {0, 1, 0},
            {1, 0, 0},
        };

        vertex_buffer::set_data((GLsizeiptr) (vertex_buffer_data.size() * sizeof(vertex)), &vertex_buffer_data[0]);

        return {shader_id, texture_id, vertex_array_id, vertex_buffer_id};
    }
}
