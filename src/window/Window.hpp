#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();

    ~Window();

    void swapBuffers();

    int shouldClose();

    void close();

    GLFWwindow *getGlfwWindow();

private:
    GLFWwindow *glfw_window;
};
