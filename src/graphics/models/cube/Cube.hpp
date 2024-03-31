#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../shader/Shader.hpp"
#include "../../texture/Texture.hpp"
#include "../../buffer/VertexArray.hpp"
#include "../../../world/chunk/Chunk.hpp"

using std::vector;

struct offset {
    GLint x_offset;
    GLint y_offset;
    GLint z_offset;
    GLint face_index;
    GLint texture_index;
};

struct Mesh {
    Position position;
    std::vector<offset> mesh;
};

class Cube {
public:
    Shader shader{};
    Texture texture{};
    VertexArray cube_array{};
    GLsizei triangle_count{};
    GLsizei instance_count{};
    vector<offset> offset_data{};
    VertexBuffer offset_buffer{};

    Cube();

    void setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) const;

    static void chunkToMesh(const Chunk &chunk, vector<offset> &mesh, const std::vector<Chunk> &chunks);

    void combineMeshes(const vector<Mesh> &meshes);

private:
    [[nodiscard]] static int pos(int block_x, int block_y, int block_z);
};
