#include "shader.hpp"

string parse_shader(const string &file_path) {
    ifstream stream(file_path);

    stringstream string_stream;
    string_stream << stream.rdbuf();

    return string_stream.str();
}

GLuint compile_shader(const string &file_path, GLenum shader_type) {
    GLuint id = glCreateShader(shader_type);

    string shader_source = parse_shader(file_path);
    const char *source_char = shader_source.c_str();

    glShaderSource(id, 1, &source_char, nullptr);
    glCompileShader(id);

    return id;
}

namespace shader {
    GLuint create(const string &vertex_shader_file_path, const string &fragment_shader_file_path) {
        GLuint vertex_shader = compile_shader(vertex_shader_file_path, GL_VERTEX_SHADER);
        GLuint fragment_shader = compile_shader(fragment_shader_file_path, GL_FRAGMENT_SHADER);

        GLuint id = glCreateProgram();
        glAttachShader(id, vertex_shader);
        glAttachShader(id, fragment_shader);

        glLinkProgram(id);
        glValidateProgram(id);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        return id;
    }

    void bind(GLuint id) {
        glUseProgram(id);
    }

    void unbind() {
        glUseProgram(0);
    }

    void destroy(GLuint id) {
        glDeleteProgram(id);
    }
}
