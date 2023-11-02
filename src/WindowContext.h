class WindowContext {
public:
    GLFWwindow *window;
    unsigned int window_width{1920};
    unsigned int window_height{1080};

    WindowContext() {
        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(window_width, window_height, "Test", nullptr, nullptr);

        glfwMakeContextCurrent(window);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        glfwSwapInterval(1);
    }

    [[nodiscard]] int window_should_close() const {
        return glfwWindowShouldClose(window);
    }

    void swap_buffers() const {
        glfwSwapBuffers(window);
    }

    static void handle_events() {
        glfwPollEvents();
    }

    static void terminate() {
        glfwTerminate();
    }
};
