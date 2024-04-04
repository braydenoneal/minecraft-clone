#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../shader/Shader.hpp"
#include "../../texture/Texture.hpp"
#include "../../buffer/VertexArray.hpp"
#include "../../../world/chunk/Chunk.hpp"

#pragma pack(push, 1)
struct offset {
    GLint x_offset;
    GLint y_offset;
    GLint z_offset;
    GLubyte face_index;
    GLubyte texture_index;
    GLubyte occlusion_nn;
    GLubyte occlusion_np;
    GLubyte occlusion_pn;
    GLubyte occlusion_pp;
};
#pragma pack(pop)

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
    VertexBuffer offset_buffer{};

    Cube();

    void setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) const;

    static void chunkToMesh(const Chunk &chunk, std::vector<offset> &mesh, const std::vector<Chunk> &chunks);

    void setMesh(std::vector<offset> &total_mesh);

private:
    [[nodiscard]] static int pos(int block_x, int block_y, int block_z);
};
