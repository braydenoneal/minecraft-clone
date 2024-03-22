#include "shader.hpp"

string parse_shader(const string &file_path) {
    ifstream stream(file_path);

    stringstream string_stream;
    string_stream << stream.rdbuf();

    return string_stream.str();
}

GLuint compile_shader(const string &file_path, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);

    string shader_source = parse_shader(file_path);
    const char *source_char = shader_source.c_str();

    glShaderSource(shader, 1, &source_char, nullptr);
    glCompileShader(shader);

    return shader;
}

namespace shader {
    GLuint create_shaders(const string &vertex_shader_file_path, const string &fragment_shader_file_path) {
        GLuint vertex_shader = compile_shader(vertex_shader_file_path, GL_VERTEX_SHADER);
        GLuint fragment_shader = compile_shader(fragment_shader_file_path, GL_FRAGMENT_SHADER);

        GLuint shader_id = glCreateProgram();
        glAttachShader(shader_id, vertex_shader);
        glAttachShader(shader_id, fragment_shader);

        glLinkProgram(shader_id);
        glValidateProgram(shader_id);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return shader_id;
    }

    void bind(GLuint shader_id) {
        glUseProgram(shader_id);
    }

    void unbind() {
        glUseProgram(0);
    }

    void destroy(GLuint shader_id) {
        glDeleteProgram(shader_id);
    }
}
