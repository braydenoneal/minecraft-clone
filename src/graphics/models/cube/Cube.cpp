#include <iostream>
#include "Cube.hpp"

Cube::Cube() {
    shader.setShaders("../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
    shader.bind();

    texture.setTextures({"../res/textures/grass_block_side.png",
                         "../res/textures/grass_block_top.png",
                         "../res/textures/dirt.png"}, 16, 16);
    texture.bind();

    shader.setUniform1i("u_textures", 0);

    struct vertex {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat texture_x;
        GLfloat texture_y;
    };

    vector<vertex> vertex_buffer_data = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 1, 1, 1, 1},
    };

    triangle_count = (GLsizei) vertex_buffer_data.size();

    VertexBuffer cube_buffer{};
    cube_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(vertex)), &vertex_buffer_data[0]);

    cube_array.addAttributes(cube_buffer, {{3, GL_FLOAT, GL_FALSE}, {2, GL_FLOAT, GL_FALSE}}, 0);
    cube_array.addAttributes(offset_buffer, {{3, GL_INT, GL_FALSE}, {1, GL_INT, GL_FALSE}, {1, GL_INT, GL_FALSE}}, 1);
}

void Cube::setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) const {
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), aspect_ratio, 0.05f, 2048.0f);

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, -camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f), -camera_position);
    glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
}

void Cube::chunkToMesh(const Chunk &chunk, vector<offset> &mesh, const std::vector<Chunk> &chunks) {
    vector<offset> new_mesh{};

    std::vector<Block> blocks((CHUNK_SIZE + 2) * (CHUNK_SIZE + 2) * (CHUNK_SIZE + 2), {1});

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                blocks[pos(x, y, z)] = chunk.get(x, y, z);
            }
        }
    }

    struct Direction {
        int x;
        int y;
        int z;
    };

    std::vector<Direction> directions = {
        {-1, +0, +0}, {+1, +0, +0}, {+0, -1, +0}, {+0, +1, +0}, {+0, +0, -1}, {+0, +0, +1}, {-1, -1, +0}, {-1, +1, +0},
        {+1, -1, +0}, {+1, +1, +0}, {-1, +0, -1}, {-1, +0, +1}, {+1, +0, -1}, {+1, +0, +1}, {+0, -1, -1}, {+0, -1, +1},
        {+0, +1, -1}, {+0, +1, +1}, {-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1}, {+1, -1, -1}, {+1, -1, +1},
        {+1, +1, -1}, {+1, +1, +1},
    };

    for (auto direction: directions) {
        for (const auto &adjacent_chunk: chunks) {
            if (chunk.position.x + direction.x == adjacent_chunk.position.x
                    && chunk.position.y + direction.y == adjacent_chunk.position.y
                    && chunk.position.z + direction.z == adjacent_chunk.position.z) {
                int get_x = -direction.x * CHUNK_SIZE;
                int start_x = direction.x < 1 ? direction.x : CHUNK_SIZE;
                int end_x = start_x + (direction.x == 0 ? CHUNK_SIZE : 1);

                int get_y = -direction.y * CHUNK_SIZE;
                int start_y = direction.y < 1 ? direction.y : CHUNK_SIZE;
                int end_y = start_y + (direction.y == 0 ? CHUNK_SIZE : 1);

                int get_z = -direction.z * CHUNK_SIZE;
                int start_z = direction.z < 1 ? direction.z : CHUNK_SIZE;
                int end_z = start_z + (direction.z == 0 ? CHUNK_SIZE : 1);

                for (int x = start_x; x < end_x; x++) {
                    for (int y = start_y; y < end_y; y++) {
                        for (int z = start_z; z < end_z; z++) {
                            blocks[pos(x, y, z)] = adjacent_chunk.get(get_x + x, get_y + y, get_z + z);
                        }
                    }
                }
            }
        }
    }

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                Block block = chunk.get(x, y, z);

                if (block.id != 0) {
                    int x_offset = x + chunk.position.x * CHUNK_SIZE;
                    int y_offset = y + chunk.position.y * CHUNK_SIZE;
                    int z_offset = z + chunk.position.z * CHUNK_SIZE;

                    if (blocks[pos(x - 1, y, z)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 0, 0});
                    }
                    if (blocks[pos(x + 1, y, z)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 1, 0});
                    }

                    if (blocks[pos(x, y - 1, z)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 2, 2});
                    }
                    if (blocks[pos(x, y + 1, z)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 3, 1});
                    }

                    if (blocks[pos(x, y, z - 1)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 4, 0});
                    }
                    if (blocks[pos(x, y, z + 1)].id == 0) {
                        mesh.push_back({x_offset, y_offset, z_offset, 5, 0});
                    }
                }
            }
        }
    }

    mesh.insert(mesh.end(), new_mesh.begin(), new_mesh.end());
}

void Cube::combineMeshes(const vector<Mesh> &meshes) {
    vector<offset> total_mesh{};

    for (const Mesh &mesh: meshes) {
        total_mesh.insert(total_mesh.end(), mesh.mesh.begin(), mesh.mesh.end());
    }

    offset_data = total_mesh;
    instance_count = (GLsizei) offset_data.size();
    offset_buffer.setData((GLsizeiptr) (offset_data.size() * sizeof(offset)), &offset_data[0]);
}

int Cube::pos(int block_x, int block_y, int block_z) {
    return (block_x + 1) * (CHUNK_SIZE + 2) * (CHUNK_SIZE + 2) + (block_y + 1) * (CHUNK_SIZE + 2) + (block_z + 1);
}
