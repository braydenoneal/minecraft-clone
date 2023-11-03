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
            for (int j = 0; j < game_context->cube_count; j++) {
                glm::mat4 model_view = Transform::render_transformation(game_context->camera_position, game_context->camera_angle, glm::vec3(game_context->model_position.x + (float) i, game_context->model_position.y, game_context->model_position.z + (float) j), game_context->model_angle);
                glm::mat4 perspective = Transform::perspective_transformation(window_context->field_of_view, window_context->get_aspect_ratio(), 0.0001f, 10000.0f);
                Cube cube;
                cube.draw(perspective * model_view);
            }
        }
    }
};
