#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../shader/Shader.hpp"
#include "../../texture/Texture.hpp"
#include "../../buffer/VertexArray.hpp"

using std::vector;

class Cube {
public:
    Shader shader{};
    Texture texture{};
    VertexArray cube_array{};
    GLsizei triangle_count{};
    GLsizei instance_count{};

    Cube();

    void set_uniforms() const;
};
