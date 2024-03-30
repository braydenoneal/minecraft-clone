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

    [[nodiscard]] float getAspectRatio() const;

private:
    GLFWwindow *glfw_window;
    int width{};
    int height{};
};
