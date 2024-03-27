#include "../../shader/shader.hpp"
#include "../../texture/texture.hpp"
#include "../../buffer/vertex_array.hpp"
#include "../../buffer/vertex_buffer.hpp"
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using std::vector;

namespace cube {
    struct render_context {
        GLuint shader_id;
        GLuint texture_id;
        GLuint vertex_array_id;
        GLuint vertex_buffer_id;
    };

    render_context create_context();

    void set_uniforms(render_context cube_context);
}
