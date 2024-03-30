#pragma once

#include <glad/glad.h>
#include <vector>

#include "VertexBuffer.hpp"

struct VertexAttribute {
    GLint count;
    GLenum type;
    GLboolean normalized;

    static GLsizei getSizeOfType(GLenum type);
};

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    static void unbind();

    void addAttributes(const VertexBuffer &vertex_buffer,
                       const std::vector<VertexAttribute> &attributes,
                       GLuint divisor);

private:
    GLuint id{};
    GLuint attribute_count{};
};
