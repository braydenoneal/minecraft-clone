class Renderer {
public:
    WindowContext *window_context;
    GameContext *game_context;

    Renderer(WindowContext *input_window_context, GameContext *input_game_context) {
        window_context = input_window_context;
        game_context = input_game_context;
    }

    static void render() {
        clear();
    }

    static void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
};
