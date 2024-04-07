#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../../shader/Shader.hpp"
#include "../../../texture/Texture.hpp"
#include "../../../buffer/VertexArray.hpp"

struct PigVertex {
    float x;
    float y;
    float z;
    float u;
    float v;
    float t;
    float b;
    float ox;
    float oy;
    float oz;
    float rx;
    float ry;
    float rz;
};

class Pig {
public:
    Shader shader{};
    Texture texture{};
    VertexArray vertex_array{};
    VertexBuffer vertex_buffer{};
    GLsizei vertex_count{};
    std::vector<PigVertex> leg_back_right{};
    std::vector<PigVertex> leg_back_left{};
    std::vector<PigVertex> leg_front_right{};
    std::vector<PigVertex> leg_front_left{};
    std::vector<PigVertex> body{};
    std::vector<PigVertex> head{};

    Pig();

    void draw();

    void setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle, glm::vec3 position, glm::vec3 rotation) const;

    void setLegBackRightRotation(float x, float y, float z);

    void setLegBackLeftRotation(float x, float y, float z);

    void setLegFrontRightRotation(float x, float y, float z);

    void setLegFrontLeftRotation(float x, float y, float z);

    void setBodyRotation(float x, float y, float z);

    void setHeadRotation(float x, float y, float z);
};
