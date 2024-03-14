#pragma once

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <vector>

#include "graphics/shader.hpp"
#include "../storage/game_state.hpp"
#include "../storage/input_state.hpp"
#include "../storage/user_state.hpp"
#include "../storage/render_state.hpp"

namespace window {
    void create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, input_state::maximized ? GL_TRUE : GLFW_FALSE);

        input_state::glfw_window = glfwCreateWindow(input_state::window_width, input_state::window_height, user_state::title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(input_state::glfw_window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);

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
        float vertex_buffer_data[7 * 6 * 6] = {
                // Left -X
                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                // Right +X
                +0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.8f,
                +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.8f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.8f,
                // Bottom -Y
                -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 2.0f, 0.4f,
                -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 2.0f, 0.4f,
                +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 2.0f, 0.4f,
                -0.5f, -0.5f, +0.5f, 0.0f, 1.0f, 2.0f, 0.4f,
                // Top +Y
                -0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
                +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
                // Front -Z
                -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                // Back +Z
                +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.6f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.6f,
                +0.5f, +0.5f, +0.5f, 1.0f, 1.0f, 0.0f, 0.6f,
                -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 0.0f, 0.6f,
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * 7, (GLvoid *) nullptr);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 4 * 7, (const void *) (intptr_t) (4 * 3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 4 * 7, (const void *) (intptr_t) (4 * 6));

        render_state::program = shader::create_shaders("../res/vertex.glsl", "../res/fragment.glsl");

        shader::bind(render_state::program);

        // Textures
        std::vector<std::string> texture_paths = {"../res/textures/grass_block_side.png",
                                                  "../res/textures/grass_block_top.png", "../res/textures/dirt.png"};
        stbi_set_flip_vertically_on_load(1);

        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 16);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, 16, 16, (int) texture_paths.size(), 0, GL_RGBA,
                     GL_UNSIGNED_INT_8_8_8_8_REV, nullptr);

        unsigned char *local_buffer;

        int texture_width;
        int texture_height;
        int texture_bbp;

        for (int i = 0; i < texture_paths.size(); i++) {
            local_buffer = stbi_load(texture_paths[i].c_str(), &texture_width, &texture_height, &texture_bbp, 4);
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, texture_width, texture_height, 1, GL_RGBA,
                            GL_UNSIGNED_BYTE, local_buffer);
        }

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

    void update() {}

    void render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 perspective = glm::perspective(glm::radians(70.0f), (float) input_state::window_width / (float) input_state::window_height, 0.01f, 10000.0f);
        auto camera_rotate = glm::mat4(1.0f);
        camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, game_state::camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 camera_translate = glm::translate(
                glm::mat4(1.0f),
                glm::vec3(-game_state::camera_position.x, -game_state::camera_position.y, game_state::camera_position.z)
        );
        glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

        int location = glGetUniformLocation(render_state::program, "u_camera");
        glUniformMatrix4fv(location, 1, GL_FALSE, &camera_matrix[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        // Jump Test
        if (game_state::jumping) {
            game_state::jump_counter++;

            if (game_state::jump_counter < 32) {
                game_state::camera_position.y += 0.1f;
            } else {
                game_state::jump_counter = 0;
                game_state::jumping = false;
            }
        } else {
            game_state::camera_position.y = std::max(0.0f, game_state::camera_position.y - 0.1f);
        }
        // End Jump Test

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");
        ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(input_state::glfw_window);
    }
}
