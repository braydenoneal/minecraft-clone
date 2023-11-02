class Input {
public:
    WindowContext *window_context;
    GameContext *game_context;

    Input(WindowContext *input_window_context, GameContext *input_game_context) {
        window_context = input_window_context;
        game_context = input_game_context;
    }
};
