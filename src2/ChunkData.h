#include <vector>
#include <array>
#include <glm/gtc/noise.hpp>

const unsigned int chunk_size = 16;

class ChunkData {
public:
    typedef unsigned int block_id_t;
    typedef std::array<block_id_t, chunk_size * chunk_size * chunk_size> chunk_data_t;

    typedef std::array<float, 10> vertex_t;
    typedef std::array<vertex_t, 5> face_t;

    typedef std::vector<face_t> mesh_data_t;

    static unsigned int get_chunk_position(unsigned int x, unsigned int y, unsigned int z) {
        return x * chunk_size * chunk_size + y * chunk_size + z;
    }

    static chunk_data_t get_flat_chunk_data() {
        chunk_data_t chunk_data{0};

        for (int x = 0; x < chunk_size; x++) {
            for (int z = 0; z < chunk_size; z++) {
                chunk_data[get_chunk_position(x, 4, z)] = 1;
            }
        }

        return chunk_data;
    }

    static chunk_data_t get_perlin_chunk_data(int cx, int cz) {
        chunk_data_t chunk_data{0};

        for (int x = 0; x < chunk_size; x++) {
            for (int z = 0; z < chunk_size; z++) {
                int y = 8 + (int) roundf(chunk_size / 2 * glm::perlin(glm::vec2((float) (x + cx * chunk_size) / chunk_size, (float) (z + cz * chunk_size) / chunk_size)));
                chunk_data[get_chunk_position(x, y, z)] = 1;
            }
        }

        return chunk_data;
    }

    static std::vector<chunk_data_t> get_flat_chunks(int size) {
        std::vector<chunk_data_t> chunk_data{};

        for (int x = 0; x < size; x++) {
            for (int z = 0; z < size; z++) {
                chunk_data.push_back(get_perlin_chunk_data(x, z));
            }
        }

        return chunk_data;
    }

    static face_t get_positive_x_face(int x, int y, int z) {
        return {
                vertex_t { 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
        };
    }

    static face_t get_negative_x_face(int x, int y, int z) {
        return {
                vertex_t { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.8f, (float) x, (float) y, (float) z },
        };
    }

    static face_t get_positive_y_face(int x, int y, int z) {
        return {
                vertex_t { -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  1.0f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  1.0f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  1.0f,  1.0f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  1.0f,  1.0f, (float) x, (float) y, (float) z },
        };
    }

    static face_t get_negative_y_face(int x, int y, int z) {
        return {
                vertex_t {  0.5f, -0.5f,  0.5f,  0.0f,  1.0f,  2.0f,  0.4f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  2.0f,  0.4f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  2.0f,  0.4f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f,  0.5f,  1.0f,  1.0f,  2.0f,  0.4f, (float) x, (float) y, (float) z },
        };
    }

    static face_t get_positive_z_face(int x, int y, int z) {
        return {
                vertex_t {  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
        };
    }

    static face_t get_negative_z_face(int x, int y, int z) {
        return {
                vertex_t { -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t { -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
                vertex_t {  0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  0.0f,  0.6f, (float) x, (float) y, (float) z },
        };
    }

    static mesh_data_t get_chunk_mesh(chunk_data_t chunk_data) {
        mesh_data_t mesh_data{};

        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    if (chunk_data[get_chunk_position(x, y, z)] > 0) {
                        if (x == 15 || (x < 15 && chunk_data[get_chunk_position(x + 1, y, z)] == 0))
                            mesh_data.push_back(get_positive_x_face(x, y, z));
                        if (x == 0  || (x > 0  && chunk_data[get_chunk_position(x - 1, y, z)] == 0))
                            mesh_data.push_back(get_negative_x_face(x, y, z));
                        if (y == 15 || (y < 15 && chunk_data[get_chunk_position(x, y + 1, z)] == 0))
                            mesh_data.push_back(get_positive_y_face(x, y, z));
                        if (y == 0  || (y > 0  && chunk_data[get_chunk_position(x, y - 1, z)] == 0))
                            mesh_data.push_back(get_negative_y_face(x, y, z));
                        if (z == 15 || (z < 15 && chunk_data[get_chunk_position(x, y, z + 1)] == 0))
                            mesh_data.push_back(get_positive_z_face(x, y, z));
                        if (z == 0  || (z > 0  && chunk_data[get_chunk_position(x, y, z - 1)] == 0))
                            mesh_data.push_back(get_negative_z_face(x, y, z));
                    }
                }
            }
        }

        return mesh_data;
    }

    static std::vector<mesh_data_t> get_chunk_meshes(const std::vector<chunk_data_t> &chunk_datas) {
        std::vector<mesh_data_t> chunk_meshes{};

        for (chunk_data_t chunk_data : chunk_datas) {
            chunk_meshes.push_back(get_chunk_mesh(chunk_data));
        }

        return chunk_meshes;
    }

    static std::vector<unsigned int> get_indices_of_size(unsigned long long faces_count) {
        std::vector<unsigned int> indices{};

        for (int i = 0; i < faces_count; i++) {
            indices.push_back(i * 5 + 0);
            indices.push_back(i * 5 + 1);
            indices.push_back(i * 5 + 2);
            indices.push_back(i * 5 + 3);
            indices.push_back(i * 5 + 4);
            indices.push_back(i * 5 + 1);
        }

        return indices;
    }
};
