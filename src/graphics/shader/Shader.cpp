#include "Shader.hpp"

Shader::Shader() {
    id = glCreateProgram();
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::setShaders(const std::string &vertex_shader_file_path,
                        const std::string &fragment_shader_file_path) const {
    GLuint vertex_shader = compile_shader(vertex_shader_file_path, GL_VERTEX_SHADER);
    GLuint fragment_shader = compile_shader(fragment_shader_file_path, GL_FRAGMENT_SHADER);

    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);
    glValidateProgram(id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setUniformMatrix4fv(const GLchar *name, const GLfloat *value) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, value);
}

void Shader::setUniform4fv(const GLchar *name, const GLfloat *value) const {
    glUniform4fv(glGetUniformLocation(id, name), 1, value);
}

void Shader::setUniform3fv(const GLchar *name, const GLfloat *value) const {
    glUniform3fv(glGetUniformLocation(id, name), 1, value);
}

void Shader::setUniform1i(const GLchar *name, GLint value) const {
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setUniform1f(const GLchar *name, GLfloat value) const {
    glUniform1f(glGetUniformLocation(id, name), value);
}

std::string Shader::parse_shader(const std::string &file_path) {
    std::ifstream stream(file_path);

    std::stringstream string_stream;
    string_stream << stream.rdbuf();

    return string_stream.str();
}

GLuint Shader::compile_shader(const std::string &file_path, GLenum shader_type) {
    GLuint id = glCreateShader(shader_type);

    std::string shader_source = parse_shader(file_path);
    const char *source_char = shader_source.c_str();

    glShaderSource(id, 1, &source_char, nullptr);
    glCompileShader(id);

    return id;
}
