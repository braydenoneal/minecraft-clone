#include "../../shader/Shader.hpp"
#include "../../texture/Texture.hpp"
#include "../../buffer/VertexArray.hpp"

struct Vertex {
    float x;
    float y;
};

class Crosshair {
public:
    Shader shader{};
    Texture texture{};
    VertexArray vertex_array{};
    VertexBuffer vertex_buffer{};
    std::vector<Vertex> vertex_data{};
    GLsizei vertex_count{};

    Crosshair();

    void draw() const;

    void setUniforms(float aspect_ratio, float width) const;
};
