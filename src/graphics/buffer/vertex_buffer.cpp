#include "vertex_buffer.hpp"

namespace vertex_buffer {
    GLuint create() {
        GLuint id;

        glGenBuffers(1, &id);

        return id;
    }

    void bind(GLuint id) {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void set_data(GLsizeiptr size, const GLvoid *data) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void render(GLsizei count) {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }

    void unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void destroy(GLuint id) {
        glDeleteBuffers(1, &id);
    }
}
