#include <glad/glad.h>

class VertexBuffer {
public:
    VertexBuffer();

    ~VertexBuffer();

    void bind() const;

    static void unbind();

    void setData(GLsizeiptr size, const GLvoid *data) const;

private:
    GLuint id{};
};
