#include "Context.h"

int main() {
    WindowContext window_context;
    GameContext game_context;
    Input input(&window_context, &game_context);
    GuiContext gui_context(&window_context, &game_context);
    Renderer renderer(&window_context, &game_context);

    int quad_count = 6 * Chunk::size * Chunk::size;

    Cube cube(quad_count, &Chunk::flat_chunk_positions()[0], &Chunk::flat_chunk_indices()[0]);
    Draw draw(&window_context, &game_context, &cube);

    while(!window_context.window_should_close()) {
        WindowContext::handle_events();
        input.do_actions();
        renderer.render();
        draw.draw();
        gui_context.render();
        window_context.swap_buffers();
    }

    GuiContext::terminate();
    WindowContext::terminate();

    return 0;
}
