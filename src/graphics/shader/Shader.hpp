#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

class Shader {
public:
    Shader();

    ~Shader();

    void setShaders(const std::string &vertex_shader_file_path, const std::string &fragment_shader_file_path) const;

    void bind() const;

    static void unbind();

    void setUniformMatrix4fv(const GLchar *name, const GLfloat *value) const;

    void setUniform1i(const GLchar *name, GLint value) const;

    void setUniform1f(const GLchar *name, GLfloat value) const;

private:
    GLuint id{};

    static std::string parse_shader(const std::string &file_path);

    static GLuint compile_shader(const std::string &file_path, GLenum shader_type);
};
