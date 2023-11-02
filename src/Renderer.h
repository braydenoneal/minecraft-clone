class Renderer {
public:
    static void render() {
        clear();
    }

    static void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};
