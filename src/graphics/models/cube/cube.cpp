#include "cube.hpp"
#include "iostream"

namespace cube {
    render_context create_context() {

        GLuint vertex_buffer_id = vertex_buffer::create();
        vertex_buffer::bind(vertex_buffer_id);

        GLuint vertex_array_id = vertex_array::create({
            {3, GL_FLOAT, GL_FALSE},
            {1, GL_UNSIGNED_BYTE, GL_FALSE},
        });
        vertex_array::bind(vertex_array_id);

        GLuint shader_id = shader::create("../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
        shader::bind(shader_id);

        GLuint texture_id = texture::create(
            {"../res/textures/grass_block_side.png"}, 16, 16
        );
        texture::bind(texture_id);

        int texture_uniform = glGetUniformLocation(shader_id, "u_textures");
        glUniform1i(texture_uniform, 0);

        #pragma pack(push, 1)
        struct vertex {
            GLfloat x;
            GLfloat y;
            GLfloat z;
            GLubyte t;
        };
        #pragma pack(pop)

        vector<vertex> vertex_buffer_data = {
            {1, 0, -5, 2},
            {0, 0, -5, 0},
            {1, 1, -5, 3},

            {0, 1, -5, 1},
            {1, 1, -5, 3},
            {0, 0, -5, 0},
        };

        vertex_buffer::set_data((GLsizeiptr) (vertex_buffer_data.size() * sizeof(vertex)), &vertex_buffer_data[0]);

        std::cout << sizeof(vertex) << std::endl;

        return {shader_id, texture_id, vertex_array_id, vertex_buffer_id};
    }

    void set_uniforms(render_context cube_context) {
        glm::mat4 perspective = glm::perspective(
            glm::radians(70.0f),
            (float) 640 / (float) 480,
            0.05f, 2048.0f
        );

        auto camera_rotate = glm::mat4(1.0f);

        camera_rotate = glm::rotate(camera_rotate, -0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, -0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, -0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f), -glm::vec3(0, 0, 0));

        glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

        int location = glGetUniformLocation(cube_context.shader_id, "u_camera");
        glUniformMatrix4fv(location, 1, GL_FALSE, &camera_matrix[0][0]);
    }
}
