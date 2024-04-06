#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../shader/Shader.hpp"
#include "../../texture/Texture.hpp"
#include "../../buffer/VertexArray.hpp"

struct BoundingBoxVertex {
    float x;
    float y;
    float z;
};

class BoundingBox {
public:
    Shader shader{};
    Texture texture{};
    VertexArray vertex_array{};
    VertexBuffer vertex_buffer{};
    GLsizei vertex_count{};

    BoundingBox();

    void draw() const;

    void setUniforms(float aspect_ratio, glm::vec3 camera_angle) const;
};
