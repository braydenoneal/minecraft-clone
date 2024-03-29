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

    Cube();

    void set_uniforms() const;
};
