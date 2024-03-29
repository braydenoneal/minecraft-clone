#include <glad/glad.h>

class VertexBuffer {
public:
    VertexBuffer();

    void bind() const;

    static void unbind();

    ~VertexBuffer();

    void setData(GLsizeiptr size, const GLvoid *data) const;

private:
    GLuint id{};
};
