class Action {
public:
    static void do_action(int key_code, WindowContext *window_context, GameContext *game_context) {
        switch (key_code) {
            case GLFW_KEY_W:
                game_context->camera_position.z += 0.1f;
                break;
            case GLFW_KEY_S:
                game_context->camera_position.z -= 0.1f;
                break;
            default:
                break;
        }
    }
};
