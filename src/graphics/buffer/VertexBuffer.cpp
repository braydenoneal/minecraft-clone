#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer(GLsizeiptr size, const GLvoid *data) {
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &id);
}
