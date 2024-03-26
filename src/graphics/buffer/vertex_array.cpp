#include "vertex_array.hpp"

GLsizei get_size_of_type(GLenum type) {
    switch (type) {
        case GL_FLOAT:
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        default:
            return 0;
    }
}

namespace vertex_array {
    GLuint create(const vector<attribute> &attributes) {
        GLuint id;
        glGenVertexArrays(1, &id);

        GLsizei stride = 0;

        for (attribute current_attribute: attributes) {
            stride += get_size_of_type(current_attribute.type) * current_attribute.count;
        }

        GLuint current_index = 0;
        GLint current_pointer = 0;

        for (attribute current_attribute: attributes) {
            glVertexAttribPointer(
                current_index,
                current_attribute.count,
                current_attribute.type,
                current_attribute.normalized,
                stride,
                (const GLvoid *) (intptr_t) current_pointer
            );

            current_index++;
            current_pointer += get_size_of_type(current_attribute.type) * current_attribute.count;
        }

        return id;
    }

    void bind(GLuint id) {
        glBindVertexArray(id);
    }

    void unbind() {
        glBindVertexArray(0);
    }

    void destroy(GLuint id) {
        glDeleteVertexArrays(1, &id);
    }
}