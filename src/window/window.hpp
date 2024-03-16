#pragma once

#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <chrono>

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

namespace window {
    int cube_count = 0;
    int x_region = 0;
    int z_region = 0;

    std::vector<chunk::chunk> chunks;
    std::vector<chunk::chunk_mesh> chunk_meshes;
    std::vector<float> total_mesh;
    std::queue<chunk::chunk_location> chunk_queue;

    void rerender() {
        std::vector<chunk::chunk_location> chunk_locations = {};

        for (int x = x_region - user_state::chunk_radius; x <= x_region + user_state::chunk_radius; x++) {
            for (int z = z_region - user_state::chunk_radius; z <= z_region + user_state::chunk_radius; z++) {
                if (pow((float) x + 0.5f - (float) x_region + 0.5f, 2) + pow((float) z + 0.5f - (float) z_region + 0.5f, 2) < user_state::chunk_radius * user_state::chunk_radius) {
                    chunk_locations.push_back({x, z});
                }
            }
        }

        // Unload chunk datas
        std::vector<chunk::chunk_location> chunk_data_delete_chunk_locations = {};

        for (auto &chunk : chunks) {
            bool delete_chunk = true;

            for (auto chunk_location: chunk_locations) {
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

        // Load chunks
        for (auto chunk_location: chunk_locations) {
            bool add_mesh = true;

            for (const auto &chunk_data: chunks) {
                if (chunk_location.x == chunk_data.x && chunk_location.z == chunk_data.z) {
                    add_mesh = false;
                }
            }

            if (add_mesh) {
                chunk_queue.push({chunk_location.x, chunk_location.z});
            }
        }
    }

    void render_queue() {
        chunk::chunk_location chunk_location = chunk_queue.front();

        chunk_queue.pop();

        chunk::chunk chunk_data = cube::chunk_location_to_block_data(chunk_location.x, chunk_location.z);

        chunks.push_back(chunk_data);

        chunk::chunk_mesh chunk_mesh = cube::chunk_data_to_mesh(chunk_data);

        chunk_meshes.push_back(chunk_mesh);

        total_mesh = cube::chunk_meshes_to_total_mesh(chunk_meshes);

        cube_count = std::ceil((float) total_mesh.size() / 7.0f);

        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) total_mesh.size() * 4, &total_mesh[0], GL_STATIC_DRAW);
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

        rerender();

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

    void render() {
        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glClearColor(138.0f / 255.0f, 163.0f / 255.0f, 1.0f, 1.0f);
        glClearColor(127.0f / 255.0f, 204.0f / 255.0f, 1.0f, 1.0f);

        // Chunk loading
        {
            int next_x_region = std::floor(game_state::camera_position.x / (float) cube::chunk_size);
            int next_z_region = std::ceil(-game_state::camera_position.z / (float) cube::chunk_size);

            // Region changed
            if (!user_state::pause_chunk_loading && next_x_region != x_region || next_z_region != z_region) {
                chunk_queue = {};
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
            glm::mat4 perspective = glm::perspective(glm::radians(user_state::field_of_view),
                                                     (float) input_state::window_width /
                                                     (float) input_state::window_height,
                                                     0.05f, 2048.0f);
            auto camera_rotate = glm::mat4(1.0f);
            camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
            camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
            camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));
            glm::mat4 camera_translate = glm::translate(
                    glm::mat4(1.0f),
                    glm::vec3(-game_state::camera_position.x, -game_state::camera_position.y,
                              game_state::camera_position.z)
            );
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
                facing_text += "+Z North";
            } else if (direction > 0.25f && direction <= 0.75f) {
                facing_text += "+X East";
            } else if (direction > 0.75f || direction < -0.75f) {
                facing_text += "-Z South";
            } else if (direction > -0.75f && direction <= -0.25f) {
                facing_text += "-X West";
            }
            ImGui::Text(facing_text.c_str());
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
