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
#include "../matter/matter.hpp"

namespace window {
    static bool maximized = true;
    static std::string title = "Graphics Application Template";
    static int width = 1920;
    static int height = 1080;
    static double cursor_x = 0.0;
    static double cursor_y = 0.0;
    static double cursor_difference_x = 0.0;
    static double cursor_difference_y = 0.0;
    static GLuint program;
    static GLuint vertex_array;
    static GLuint vertex_buffer;

    static GLFWwindow *glfw_window;

    void create_context() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_MAXIMIZED, maximized ? GL_TRUE : GLFW_FALSE);

        glfw_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(glfw_window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);

        glfwGetWindowSize(glfw_window, &width, &height);
        glfwGetCursorPos(glfw_window, &cursor_x, &cursor_y);
        glfwSetInputMode(glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetInputMode(glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(glfw_window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
        ImGui::StyleColorsDark();

        // Render Setup
        glGenVertexArrays(1, &vertex_array);
        glBindVertexArray(vertex_array);

        glGenBuffers(1, &vertex_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
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

        program = shader::create_shaders(
                "../res/vertex.glsl",
                "../res/fragment.glsl"
        );

        shader::bind(program);

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

        int texture_uniform = glGetUniformLocation(program, "u_textures");
        glUniform1i(texture_uniform, 0);
    }

    int should_close() {
        return glfwWindowShouldClose(glfw_window);
    }

    void terminate() {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();

        glDeleteProgram(program);
        glDeleteBuffers(1, &vertex_buffer);
        glDeleteVertexArrays(1, &vertex_array);

        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void close() {
        glfwSetWindowShouldClose(glfw_window, GLFW_TRUE);
    }

    GLFWwindow *get_glfw_window() {
        return glfw_window;
    }

    void toggle_maximize() {
        maximized = !maximized;

        if (maximized) {
            glfwMaximizeWindow(glfw_window);
        } else {
            glfwRestoreWindow(glfw_window);
        }
    }

    void update() {}

    void render() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 perspective = glm::perspective(glm::radians(70.0f), (float) width / (float) height, 0.01f,
                                                 10000.0f);
        auto camera_rotate = glm::mat4(1.0f);
        camera_rotate = glm::rotate(camera_rotate, matter::camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, matter::camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
        camera_rotate = glm::rotate(camera_rotate, matter::camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 camera_translate = glm::translate(
                glm::mat4(1.0f),
                glm::vec3(-matter::camera_position.x, -matter::camera_position.y, matter::camera_position.z)
        );
        glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

        int location = glGetUniformLocation(program, "u_camera");
        glUniformMatrix4fv(location, 1, GL_FALSE, &camera_matrix[0][0]);

        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Debug");
        ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(glfw_window);
    }
}
