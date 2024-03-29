#include "../../shader/shader.hpp"
#include "../../texture/Texture.hpp"
#include "vector"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../../buffer/VertexArray.hpp"

using std::vector;

struct render_context {
    GLuint shader_id;
};

class cube {
public:
    VertexArray cube_array{};
    Texture texture{};

    render_context create_context();

    static void set_uniforms(const render_context& cube_context);
};
