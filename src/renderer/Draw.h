class Draw {
public:
    WindowContext *window_context;
    GameContext *game_context;

    Draw(WindowContext *input_window_context, GameContext *input_game_context) {
        window_context = input_window_context;
        game_context = input_game_context;
    }

    void draw() const {
        for (int i = 0; i < game_context->cube_count; i++) {
            glm::mat4 model_view = Transform::render_transformation(game_context->camera_position, game_context->camera_angle, game_context->model_position, game_context->model_angle);
            glm::mat4 perspective = Transform::perspective_transformation(window_context->field_of_view, window_context->get_aspect_ratio(), 0.0001f, 10000.0f);
            Cube::draw(perspective * model_view);
        }
    }
};
