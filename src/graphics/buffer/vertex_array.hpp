#include "glad/glad.h"
#include "vector"

using std::vector;

namespace vertex_array {
    struct attribute {
        GLint count;
        GLenum type;
        GLboolean normalized;
        GLuint divisor;
    };

    GLuint create(const vector<attribute> &attributes);

    void add_attributes(const vector<attribute> &attributes, GLuint starting_index);

    void bind(GLuint id);

    void unbind();

    void destroy(GLuint id);
}
