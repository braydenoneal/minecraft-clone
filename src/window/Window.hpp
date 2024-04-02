#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mutex>

class Window {
public:
    Window(std::mutex &_m_reference);

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
    std::mutex &_m;
};
