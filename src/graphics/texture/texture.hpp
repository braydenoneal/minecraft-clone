#include "glad/glad.h"
#include "vector"
#include "string"
#include "stb_image.h"

namespace texture {
    GLuint create_textures(const std::vector<std::string> &texture_file_paths, GLuint texture_width, GLuint texture_height);

    void bind(GLuint texture_id);

    void unbind();

    void destroy(GLuint texture_id);
}
