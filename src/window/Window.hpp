#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window();

    void swapBuffers();

    int shouldClose();

    void close();

    GLFWwindow *getGlfwWindow();

    ~Window();

private:
    GLFWwindow *glfw_window;
};
