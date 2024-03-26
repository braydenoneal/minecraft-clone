#include "glad/glad.h"
#include "vector"
#include "string"
#include "stb_image.h"

using std::vector, std::string;

namespace texture {
    GLuint create(const vector<string> &file_paths, GLint width, GLint height);

    void bind(GLuint id);

    void unbind();

    void destroy(GLuint id);
}
