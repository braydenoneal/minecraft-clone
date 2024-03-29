#include <iostream>
#include "VertexArray.hpp"

GLsizei VertexAttribute::getSizeOfType(GLenum type) {
    switch (type) {
        case GL_FLOAT:
        case GL_UNSIGNED_INT:
        case GL_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        default:
            return 0;
    }
}

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::addAttributes(const VertexBuffer &vertex_buffer,
                                const std::vector<VertexAttribute> &attributes,
                                GLuint divisor) {
    bind();
    vertex_buffer.bind();

    GLsizei stride = 0;

    for (VertexAttribute attribute: attributes) {
        stride += VertexAttribute::getSizeOfType(attribute.type) * attribute.count;
    }

    GLint current_pointer = 0;

    for (VertexAttribute attribute: attributes) {
        glEnableVertexAttribArray(attribute_count);

        if (attribute.type != GL_INT) {
            glVertexAttribPointer(
                attribute_count,
                attribute.count,
                attribute.type,
                attribute.normalized,
                stride,
                (const GLvoid *) (intptr_t) current_pointer
            );
        } else {
            glVertexAttribIPointer(
                attribute_count,
                attribute.count,
                attribute.type,
                stride,
                (const GLvoid *) (intptr_t) current_pointer
            );
        }

        glVertexAttribDivisor(attribute_count, divisor);

        attribute_count++;
        current_pointer += VertexAttribute::getSizeOfType(attribute.type) * attribute.count;
    }

    VertexBuffer::unbind();
    unbind();
}
