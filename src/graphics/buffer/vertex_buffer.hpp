#include "glad/glad.h"

namespace vertex_buffer {
    GLuint create();

    void bind(GLuint id);

    void set_data(GLsizeiptr size, const GLvoid *data);

    void render(GLsizei count);

    void unbind();

    void destroy(GLuint id);
}
