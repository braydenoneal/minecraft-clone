#include "glad/glad.h"
#include "string"
#include "fstream"
#include "sstream"

using std::string, std::ifstream, std::stringstream;

namespace shader {
    GLuint create_shaders(const string &vertex_shader_file_path, const string &fragment_shader_file_path);

    void bind(GLuint shader_id);

    void unbind();

    void destroy(GLuint shader_id);
}
