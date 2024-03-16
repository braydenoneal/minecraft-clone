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

namespace window {
    int cube_count = 0;
    int x_region = 0;
    int z_region = 0;
    std::map<std::array<int, 2>, std::vector<float>> chunk_locations_to_buffer_data;
    std::vector<float> vertex_buffer_data;
    std::queue<std::array<int, 2>> chunks_to_load;

    void rerender() {
        std::vector<std::array<int, 2>> chunk_locations = {};

        for (int x = x_region - user_state::chunk_radius; x <= x_region + user_state::chunk_radius; x++) {
            for (int z = z_region - user_state::chunk_radius; z <= z_region + user_state::chunk_radius; z++) {
                if (pow((float) x + 0.5f - (float) x_region + 0.5f, 2) + pow((float) z + 0.5f - (float) z_region + 0.5f, 2) < user_state::chunk_radius * user_state::chunk_radius) {
                    chunk_locations.push_back({x, z});
                }
            }
        }

        // Unload chunks
        std::vector<std::array<int, 2>> unload_chunks = {};

        for (const auto &[key, value]: chunk_locations_to_buffer_data) {
            bool del = true;

            for (std::array<int, 2> chunk_location: chunk_locations) {
                if (key == chunk_location) {
                    del = false;
                }
            }

            if (del) {
                unload_chunks.push_back(key);
            }
        }

        for (std::array<int, 2> chunk_location: unload_chunks) {
            chunk_locations_to_buffer_data.erase(chunk_location);
        }

        // Load new chunks
        for (std::array<int, 2> chunk_location: chunk_locations) {
            if (!chunk_locations_to_buffer_data.count(chunk_location)) {
                chunks_to_load.push(chunk_location);
            }
        }
    }

    void render_queue() {
        std::vector<std::array<int, 2>> next_chunk = {chunks_to_load.front()};

        std::map<std::array<int, 2>, std::vector<float>> new_data = cube::chunk_locations_to_buffer_data(next_chunk);

        chunk_locations_to_buffer_data.merge(new_data);

        vertex_buffer_data = cube::combine_chunks(chunk_locations_to_buffer_data);

        cube_count = std::ceil((float) vertex_buffer_data.size() / 7.0f);

        glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) vertex_buffer_data.size() * 4, &vertex_buffer_data[0], GL_STATIC_DRAW);

        chunks_to_load.pop();
    }

    void create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, input_state::maximized ? GL_TRUE : GLFW_FALSE);

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
        std::vector<std::string> texture_paths = {"../res/textures/grass_block_side.png",
                                                  "../res/textures/grass_block_top.png", "../res/textures/dirt.png"};

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
        glClearColor(127.0f / 255.0f, 204.0f / 255.0f, 1.0f, 1.0f);

        // Chunk loading
        {
            int next_x_region = std::floor(game_state::camera_position.x / (float) cube::chunk_size);
            int next_z_region = std::ceil(-game_state::camera_position.z / (float) cube::chunk_size);

            if (!user_state::pause_chunk_loading && next_x_region != x_region || next_z_region != z_region) {
                chunks_to_load = {};
                rerender();
            }

            if (!user_state::pause_chunk_loading && !chunks_to_load.empty()) {
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
            chunks_to_load = {};
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
