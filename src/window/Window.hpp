#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mutex>

class Window {
public:
    Window();

    ~Window();

    void swapBuffers();

    int shouldClose();

    void close();

    void toggleMaximize();

    GLFWwindow *getGlfwWindow();

    [[nodiscard]] float getAspectRatio() const;

    void setSize(int new_width, int height);

private:
    GLFWwindow *glfw_window{};
    int width{};
    int height{};
    bool maximized{true};
    bool vsync_enabled{true};
};
