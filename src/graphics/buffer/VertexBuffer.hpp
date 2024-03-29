#include <glad/glad.h>

class VertexBuffer {
public:
    VertexBuffer(GLsizeiptr size, const GLvoid *data);

    void bind() const;

    static void unbind();

    ~VertexBuffer();

private:
    GLuint id{};
};
