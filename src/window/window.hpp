#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <stb_image.h>

#include "../render/shader.hpp"
#include "../storage/game_state.hpp"
#include "../storage/input_state.hpp"
#include "../storage/user_state.hpp"
#include "../storage/render_state.hpp"
#include "../render/models/cube.hpp"
#include "../world/chunk/chunk.hpp"
#include "../math/math.hpp"
#include "../math/timer.hpp"

namespace window {
    int cube_count = 0;
    int x_region = 0;
    int z_region = 0;
    int air_time = 0;
    bool jumping = false;
    int selected_block = 1;

    std::vector<chunk::chunk> chunks;
    std::vector<chunk::chunk_mesh> chunk_meshes;
    std::vector<float> total_mesh;
    std::queue<chunk::chunk_location> chunk_queue;

    std::vector<std::array<GLuint, 2>> hotbar_textures;

    int auto_save_counter = 0;

    void write_file_test() {
        std::ofstream wf("test.dat", std::ofstream::trunc | std::ofstream::binary);
        unsigned long blank_region = 0;
        wf.write((char *) &blank_region, sizeof(blank_region));
        wf.close();
    }

    void rerender() {
        std::vector<chunk::chunk_location> chunk_locations = {};

        for (int x = x_region - user_state::chunk_radius; x <= x_region + user_state::chunk_radius; x++) {
            for (int z = z_region - user_state::chunk_radius; z <= z_region + user_state::chunk_radius; z++) {
                if (pow(x - x_region, 2) + pow(z - z_region, 2) < pow(user_state::chunk_radius + 1, 2)) {
                    chunk_locations.push_back({x, z});
                }
            }
        }

        std::vector<chunk::chunk_location> chunk_data_locations = {};

        for (int x = x_region - user_state::chunk_radius - 1; x <= x_region + user_state::chunk_radius + 1; x++) {
            for (int z = z_region - user_state::chunk_radius - 1; z <= z_region + user_state::chunk_radius + 1; z++) {
                if (pow(x - x_region, 2) + pow(z - z_region, 2) < pow(user_state::chunk_radius + 2, 2)) {
                    chunk_data_locations.push_back({x, z});
                }
            }
        }

        // Unload chunk datas
        std::vector<chunk::chunk_location> chunk_data_delete_chunk_locations = {};

        for (auto &chunk : chunks) {
            bool delete_chunk = true;

            for (auto chunk_location: chunk_data_locations) {
                if (chunk_location.x == chunk.x && chunk_location.z == chunk.z) {
                    delete_chunk = false;
                }
            }

            if (delete_chunk) {
                chunk_data_delete_chunk_locations.push_back({chunk.x, chunk.z});
            }
        }

        for (auto chunk_location: chunk_data_delete_chunk_locations) {
            int delete_index = -1;

            for (int i = 0; i < chunks.size(); i++) {
                if (chunk_location.x == chunks[i].x && chunk_location.z == chunks[i].z) {
                    delete_index = i;
                }
            }

            chunks.erase(chunks.begin() + delete_index);
        }

        // Unload chunk meshes
        std::vector<chunk::chunk_location> chunk_meshes_delete_chunk_locations = {};

        for (auto &chunk : chunk_meshes) {
            bool delete_chunk = true;

            for (auto chunk_location: chunk_locations) {
                if (chunk_location.x == chunk.x && chunk_location.z == chunk.z) {
                    delete_chunk = false;
                }
            }

            if (delete_chunk) {
                chunk_meshes_delete_chunk_locations.push_back({chunk.x, chunk.z});
            }
        }

        for (auto chunk_location: chunk_meshes_delete_chunk_locations) {
            int delete_index = -1;

            for (int i = 0; i < chunk_meshes.size(); i++) {
                if (chunk_location.x == chunk_meshes[i].x && chunk_location.z == chunk_meshes[i].z) {
                    delete_index = i;
                }
            }

            chunk_meshes.erase(chunk_meshes.begin() + delete_index);
        }

        // Add chunk mesh to queue
        for (auto chunk_location: chunk_locations) {
            bool add_mesh = true;

            for (const auto &chunk_mesh: chunk_meshes) {
                if (chunk_location.x == chunk_mesh.x && chunk_location.z == chunk_mesh.z) {
                    add_mesh = false;
                }
            }

            if (add_mesh) {
                chunk_queue.push({chunk_location.x, chunk_location.z});
            }
        }

        // Read chunks from storage
        std::ifstream rf("test.dat", std::ifstream::out | std::ifstream::binary);

        unsigned long read_chunk_size;

        rf.read((char *) &read_chunk_size, sizeof(read_chunk_size));

        std::vector<chunk::chunk> read_chunks;

        for (int i = 0; i < read_chunk_size; i++) {
            chunk::chunk chunk_in = {0, 0};
            rf.read((char *) &chunk_in, sizeof(chunk::chunk));
            read_chunks.push_back(chunk_in);
        }

        rf.close();

        // Load chunk data
        for (auto chunk_location: chunk_data_locations) {
            bool add_chunk_data = true;

            for (const auto &chunk_data: chunks) {
                if (chunk_location.x == chunk_data.x && chunk_location.z == chunk_data.z) {
                    add_chunk_data = false;
                }
            }

            if (add_chunk_data) {
                bool generate = true;

                for (const auto &read_chunk: read_chunks) {
                    if (read_chunk.x == chunk_location.x && read_chunk.z == chunk_location.z) {
                        generate = false;
                        chunks.push_back(read_chunk);
                    }
                }

                if (generate) {
                    chunk::chunk new_chunk = cube::chunk_location_to_block_data(chunk_location.x, chunk_location.z);

                    chunks.push_back(new_chunk);

                    std::ofstream wf("test.dat", std::ofstream::app | std::ofstream::binary);

                    wf.write((char *) &new_chunk, sizeof(new_chunk));

                    wf.close();

                    std::ofstream wf2("test.dat", std::ofstream::binary | std::ofstream::in);

                    wf.seekp(0, std::ofstream::beg);

                    read_chunk_size++;
                    unsigned long chunk_size = read_chunk_size;

                    wf2.write((char *) &chunk_size, sizeof(chunk_size));

                    wf2.close();
                }
            }
        }
    }

    void render_queue() {
        chunk::chunk_location chunk_location = chunk_queue.front();

        chunk_queue.pop();

        for (const auto &chunk_data: chunks) {
            if (chunk_location.x == chunk_data.x && chunk_location.z == chunk_data.z) {
                chunk::chunk_mesh chunk_mesh = cube::chunk_data_to_mesh(chunk_data, chunks);

                chunk_meshes.push_back(chunk_mesh);

                total_mesh = cube::chunk_meshes_to_total_mesh(chunk_meshes);

                cube_count = std::ceil((float) total_mesh.size() / 7.0f);

                glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) total_mesh.size() * 4, &total_mesh[0], GL_STATIC_DRAW);
            }
        }
    }

    GLuint load_hotbar_texture(const char *path) {
        // Load from file
        stbi_set_flip_vertically_on_load(0);
        int image_width = 0;
        int image_height = 0;
        unsigned char* image_data = stbi_load(path, &image_width, &image_height, nullptr, 4);

        // Create a OpenGL texture identifier
        GLuint image_texture;
        glGenTextures(1, &image_texture);
        glBindTexture(GL_TEXTURE_2D, image_texture);

        // Setup filtering parameters for display
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        // Upload pixels into texture
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);

        return image_texture;
    }

    void setup_hotbar() {
        std::vector<std::array<std::string, 2>> paths = {
                {"../res/textures/hotbar/selected/grass.png", "../res/textures/hotbar/unselected/grass.png"},
                {"../res/textures/hotbar/selected/dirt.png", "../res/textures/hotbar/unselected/dirt.png"},
                {"../res/textures/hotbar/selected/stone.png", "../res/textures/hotbar/unselected/stone.png"},
                {"../res/textures/hotbar/selected/wood.png", "../res/textures/hotbar/unselected/wood.png"},
        };

        for (const auto &path_pair: paths) {
            GLuint selected_texture = load_hotbar_texture(path_pair[0].c_str());
            GLuint unselected_texture = load_hotbar_texture(path_pair[1].c_str());

            hotbar_textures.push_back({selected_texture, unselected_texture});
        }
    }

    void create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, input_state::maximized ? GL_TRUE : GLFW_FALSE);

        // Enable MSAA
        glfwWindowHint(GLFW_SAMPLES, 4);

        input_state::glfw_window = glfwCreateWindow(input_state::window_width, input_state::window_height,
                                                    user_state::title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(input_state::glfw_window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(user_state::vsync_enabled);

        glfwGetWindowSize(input_state::glfw_window, &input_state::window_width, &input_state::window_height);
        glfwGetCursorPos(input_state::glfw_window, &input_state::cursor_x, &input_state::cursor_y);
        glfwSetInputMode(input_state::glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(input_state::glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(input_state::glfw_window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();

        // Render Setup
        glGenVertexArrays(1, &render_state::vertex_array);
        glBindVertexArray(render_state::vertex_array);

        glGenBuffers(1, &render_state::vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, render_state::vertex_buffer);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * 7, (GLvoid *) nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * 7, (const void *) (intptr_t) (4 * 3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 4 * 7, (const void *) (intptr_t) (4 * 6));

        render_state::program = shader::create_shaders("../res/vertex.glsl", "../res/fragment.glsl");

        shader::bind(render_state::program);

        // Textures
        int texture_size = 16;
        std::vector<std::string> texture_paths = {
                "../res/textures/grass_block_side.png",
                "../res/textures/grass_block_top.png",
                "../res/textures/dirt.png",
                "../res/textures/stone.png",
                "../res/textures/wood.png",
                "../res/textures/sky.png",
        };

        stbi_set_flip_vertically_on_load(1);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, texture_size);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, texture_size, texture_size, (int) texture_paths.size(), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        unsigned char *local_buffer;

        int texture_width;
        int texture_height;
        int texture_bbp;

        for (int i = 0; i < texture_paths.size(); i++) {
            local_buffer = stbi_load(texture_paths[i].c_str(), &texture_width, &texture_height, &texture_bbp, 4);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, texture_width, texture_height, 1, GL_RGBA,
                            GL_UNSIGNED_BYTE, local_buffer);
        }

        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

        if (local_buffer) {
            stbi_image_free(local_buffer);
        }

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

        int texture_uniform = glGetUniformLocation(render_state::program, "u_textures");
        glUniform1i(texture_uniform, 0);

        setup_hotbar();

        // Reset chunk storage
//        write_file_test();

        // Reset position storage
//        {
//            std::ofstream wf("world.dat", std::ofstream::trunc | std::ofstream::binary);
//
//            glm::vec3 position = game_state::camera_position;
//
//            wf.write((char *) &position, sizeof(position));
//
//            glm::vec3 angle = game_state::camera_angle;
//
//            wf.write((char *) &angle, sizeof(angle));
//
//            wf.close();
//        }

        // Initial read from position storage
        {
            std::ifstream rf("world.dat", std::ifstream::in | std::ifstream::binary);

            glm::vec3 position;

            rf.read((char *) &position, sizeof(position));

            glm::vec3 angle;

            rf.read((char *) &angle, sizeof(angle));

            game_state::camera_position = position;
            game_state::camera_angle = angle;

            rf.close();
        }

        rerender();
    }

    int should_close() {
        return glfwWindowShouldClose(input_state::glfw_window);
    }

    void terminate() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();

        glDeleteProgram(render_state::program);
        glDeleteBuffers(1, &render_state::vertex_buffer);
        glDeleteVertexArrays(1, &render_state::vertex_array);

        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void close() {
        glfwSetWindowShouldClose(input_state::glfw_window, GLFW_TRUE);
    }

    void toggle_maximize() {
        input_state::maximized = !input_state::maximized;

        if (input_state::maximized) {
            glfwMaximizeWindow(input_state::glfw_window);
        } else {
            glfwRestoreWindow(input_state::glfw_window);
        }
    }

    void toggle_pause() {
        input_state::paused = !input_state::paused;

        if (input_state::paused) {
            glfwSetInputMode(input_state::glfw_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwSetInputMode(input_state::glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        } else {
            glfwSetInputMode(input_state::glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetInputMode(input_state::glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }
    }

    void toggle_vsync() {
        glfwSwapInterval(user_state::vsync_enabled);
    }

    int get_block_of_position(glm::vec3 position, const std::vector<chunk::chunk> &chunk_datas) {
        int chunk_x = std::floor(position.x / (float) game_state::chunk_size);
        int chunk_z = std::floor(position.z / (float) game_state::chunk_size);

        for (const auto &chunk_data: chunk_datas) {
            if (chunk_data.x == chunk_x && chunk_data.z == chunk_z) {
                int x = (int) std::floor(position.x) % game_state::chunk_size;
                int z = (int) std::floor(position.z) % game_state::chunk_size;

                if (x < 0) {
                    x += game_state::chunk_size;
                }
                if (z < 0) {
                    z += game_state::chunk_size;
                }

                int y = (int) std::floor(position.y);

                if (y >= game_state::chunk_height) {
                    return 0;
                }

                return chunk_data.blocks[chunk::pos(x, y, z)].id;
            }
        }

        return -1;
    }

    void change_block_at_position(glm::vec3 position, int block_id) {
        int chunk_x = std::floor(position.x / (float) game_state::chunk_size);
        int chunk_z = std::floor(position.z / (float) game_state::chunk_size);

        for (auto & chunk : chunks) {
            if (chunk.x == chunk_x && chunk.z == chunk_z) {
                int x = (int) std::floor(position.x) % game_state::chunk_size;
                int z = (int) std::floor(position.z) % game_state::chunk_size;

                if (x < 0) {
                    x += game_state::chunk_size;
                }
                if (z < 0) {
                    z += game_state::chunk_size;
                }

                int y = (int) std::floor(position.y);

                if (y < game_state::chunk_height && y > 0) {
                    if (chunk.blocks[chunk::pos(x, y, z)].id != block_id) {
                        chunk.blocks[chunk::pos(x, y, z)].id = block_id;

                        std::ifstream rf("test.dat", std::ifstream::in | std::ifstream::binary);

                        unsigned long read_chunk_size;

                        rf.read((char *) &read_chunk_size, sizeof(read_chunk_size));

                        for (unsigned long i = 0; i < read_chunk_size; i++) {
                            int x_read;
                            int z_read;
                            rf.seekg(sizeof(unsigned long) + i * sizeof(chunk::chunk));
                            rf.read((char *) &x_read, sizeof(int));
                            rf.seekg(sizeof(unsigned long) + i * sizeof(chunk::chunk) + sizeof(int));
                            rf.read((char *) &z_read, sizeof(int));

                            if (x_read == chunk.x && z_read == chunk.z) {
                                std::ofstream wf("test.dat", std::ofstream::binary | std::ofstream::in);

                                wf.seekp(sizeof(unsigned long) + i * sizeof(chunk::chunk));

                                wf.write((char *) &chunk, sizeof(chunk));

                                wf.close();
                            }
                        }

                        rf.close();

                        chunk_queue.push({chunk.x, chunk.z});

                        // TODO: Remove neighbor meshes
                        // Remove mesh
                        for (int i = 0; i < chunk_meshes.size(); i++) {
                            if (chunk.x == chunk_meshes[i].x && chunk.z == chunk_meshes[i].z) {
                                chunk_meshes.erase(chunk_meshes.begin() + i);
                            }
                        }
                    }
                }
            }
        }
    }

    int cast_ray(glm::vec3 start_position, glm::vec3 angle, float distance_cap, int block_id, const std::vector<chunk::chunk> &chunk_datas) {
        glm::vec3 current_position = start_position;
        glm::vec3 previous_position = start_position;
        float step_amount = 0.01f;
        float distance = 0.0f;
        int block = -1;

        while (distance < distance_cap) {
            block = get_block_of_position(current_position, chunk_datas);

            if (block > 0) {
                if (block_id > 0) {
                    change_block_at_position(previous_position, block_id);
                } else {
                    change_block_at_position(current_position, block_id);
                }
                return block;
            }

            previous_position = current_position;
            current_position = math::translate_in_angle_by_amount(current_position, angle, glm::vec3(0.0f, 0.0f, -step_amount));
            distance += step_amount;
        }

        return -1;
    }

    void place_block(int block_id) {
        cast_ray(game_state::camera_position, game_state::camera_angle, 4.0f, block_id, chunks);
    }

    bool move_camera(glm::vec3 position) {
        bool move = true;

        auto nx_ny_nz = glm::vec3(position.x - 0.3, position.y - 1.6, position.z - 0.3);
        auto nx_ny_pz = glm::vec3(position.x - 0.3, position.y - 1.6, position.z + 0.3);
        auto nx_py_nz = glm::vec3(position.x - 0.3, position.y + 0.2, position.z - 0.3);
        auto nx_py_pz = glm::vec3(position.x - 0.3, position.y + 0.2, position.z + 0.3);
        auto px_ny_nz = glm::vec3(position.x + 0.3, position.y - 1.6, position.z - 0.3);
        auto px_ny_pz = glm::vec3(position.x + 0.3, position.y - 1.6, position.z + 0.3);
        auto px_py_nz = glm::vec3(position.x + 0.3, position.y + 0.2, position.z - 0.3);
        auto px_py_pz = glm::vec3(position.x + 0.3, position.y + 0.2, position.z + 0.3);

        if (get_block_of_position(nx_ny_nz, chunks) != 0 ||
            get_block_of_position(nx_ny_pz, chunks) != 0 ||
            get_block_of_position(nx_py_nz, chunks) != 0 ||
            get_block_of_position(nx_py_pz, chunks) != 0 ||
            get_block_of_position(px_ny_nz, chunks) != 0 ||
            get_block_of_position(px_ny_pz, chunks) != 0 ||
            get_block_of_position(px_py_nz, chunks) != 0 ||
            get_block_of_position(px_py_pz, chunks) != 0) {
            move = false;
        }

        if (move) {
            game_state::camera_position = position;
        }

        return move;
    }

    void render() {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(166.0f / 255.0f, 208.0f / 255.0f, 1.0f, 1.0f);

        // Auto save
        {
            if (auto_save_counter > 600) {
                auto_save_counter = 0;
                std::cout << "Saving position..." << std::endl;

                std::ofstream wf("world.dat", std::ofstream::trunc | std::ofstream::binary);

                glm::vec3 position = game_state::camera_position;

                wf.write((char *) &position, sizeof(position));

                glm::vec3 angle = game_state::camera_angle;

                wf.write((char *) &angle, sizeof(angle));

                wf.close();
                std::cout << "Done" << std::endl;
            }

            auto_save_counter++;
        }

        // Basic collision
        {
            if (jumping) {
                float next_step_amount = 0.1f - (float) std::sqrt(air_time) / 64.0f;

                if (next_step_amount > 0) {
                    bool can_step = move_camera(glm::vec3(
                            game_state::camera_position.x,
                            game_state::camera_position.y + next_step_amount,
                            game_state::camera_position.z)
                    );

                    if (can_step) {
                        air_time++;
                    } else {
                        jumping = false;
                        air_time = 1;
                    }
                } else {
                    jumping = false;
                    air_time = 1;
                }
            } else {
                bool in_air = move_camera(glm::vec3(
                        game_state::camera_position.x,
                        game_state::camera_position.y - 0.025f * (std::sqrt(air_time + 1) / 2.0f),
                        game_state::camera_position.z)
                );

                if (in_air) {
                    air_time++;
                } else {
                    air_time = 0;
                }
            }
        }

        // Chunk loading
        {
            int next_x_region = std::floor(game_state::camera_position.x / (float) game_state::chunk_size);
            int next_z_region = std::floor(game_state::camera_position.z / (float) game_state::chunk_size);

            // Chunk location changed
            if (!user_state::pause_chunk_loading && (next_x_region != x_region || next_z_region != z_region)) {
                chunk_queue = {};
                x_region = next_x_region;
                z_region = next_z_region;
                rerender();
            }

            // Queue not empty
            if (!user_state::pause_chunk_loading && !chunk_queue.empty()) {
                render_queue();
            }

            x_region = next_x_region;
            z_region = next_z_region;
        }

        // Setup camera uniform
        {
            glm::mat4 perspective = glm::perspective(
                glm::radians(user_state::field_of_view),
                (float) input_state::window_width / (float) input_state::window_height,
                0.05f, 2048.0f
            );

            auto camera_rotate = glm::mat4(1.0f);

            camera_rotate = glm::rotate(camera_rotate, -game_state::camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
            camera_rotate = glm::rotate(camera_rotate, -game_state::camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
            camera_rotate = glm::rotate(camera_rotate, -game_state::camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

            glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f),-game_state::camera_position);

            glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

            int location = glGetUniformLocation(render_state::program, "u_camera");
            glUniformMatrix4fv(location, 1, GL_FALSE, &camera_matrix[0][0]);
        }

        // Draw geometry
        glDrawArrays(GL_TRIANGLES, 0, cube_count);

        // GUI
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Debug screen
        {
            ImGui::Begin("Debug");
            ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
            ImGui::Text("X: %.2f Y: %.2f Z: %.2f", game_state::camera_position.x, game_state::camera_position.y,
                        game_state::camera_position.z);
            ImGui::Text("P: %.2f° Y: %.2f°", -game_state::camera_angle.x / (float) M_PI * 180,
                        game_state::camera_angle.y / (float) M_PI * 180);
            std::string facing_text = "Facing: ";
            float direction = game_state::camera_angle.y / (float) M_PI;
            if (direction > -0.25f && direction <= 0.25f) {
                facing_text += "-Z North";
            } else if (direction > 0.25f && direction <= 0.75f) {
                facing_text += "-X West";
            } else if (direction > 0.75f || direction < -0.75f) {
                facing_text += "+Z South";
            } else if (direction > -0.75f && direction <= -0.25f) {
                facing_text += "+X East";
            }
            ImGui::Text(facing_text.c_str());
            ImGui::Text("Chunk: X: %d Z: %d", x_region, z_region);
            ImGui::End();
        }

        // Hotbar screen
        {
            ImGui::Begin("##Hotbar");

            for (int i = 0; i < hotbar_textures.size(); i++) {
                GLuint texture = selected_block == i + 1 ? hotbar_textures[i][0] : hotbar_textures[i][1];
                ImGui::Image((void*) (intptr_t) texture, ImVec2(64, 64));
                ImGui::SameLine();
            }

            ImGui::End();
        }

        int previous_chunk_radius = user_state::chunk_radius;
        int previous_vsync_enabled = user_state::vsync_enabled;

        // Pause screen
        if (input_state::paused) {
            ImGui::Begin("Pause");
            if (ImGui::Button("Resume")) {
                toggle_pause();
            }
            ImGui::Checkbox("Vsync", &user_state::vsync_enabled);
            ImGui::Checkbox("Pause chunk loading", &user_state::pause_chunk_loading);
            ImGui::SliderInt("Chunk radius", &user_state::chunk_radius, 2, 32);
            ImGui::SliderFloat("Field of view", &user_state::field_of_view, 10.0f, 120.0f);
            ImGui::SliderFloat("Mouse sensitivity", &user_state::mouse_sensitivity, 0.0f, 1.0f);
            if (ImGui::Button("Quit")) {
                close();
            }
            ImGui::End();
        }

        if (!user_state::pause_chunk_loading && previous_chunk_radius != user_state::chunk_radius) {
            chunk_queue = {};
            rerender();
        }

        if (previous_vsync_enabled != user_state::vsync_enabled) {
            toggle_vsync();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Next frame
        glfwSwapBuffers(input_state::glfw_window);
    }
}
