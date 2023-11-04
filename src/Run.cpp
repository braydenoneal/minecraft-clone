#include "Context.h"

int main() {
    WindowContext window_context;
    GameContext game_context;
    Input input(&window_context, &game_context);
    GuiContext gui_context(&window_context, &game_context);
    Renderer renderer(&window_context, &game_context);
    Cube cube;
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
