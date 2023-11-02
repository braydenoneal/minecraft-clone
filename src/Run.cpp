#include "Context.h"

int main() {
    WindowContext window_context;

    GuiContext::init(window_context);

    while(!window_context.window_should_close()) {
        WindowContext::handle_events();
        Renderer::render();
        GuiContext::render();
        window_context.swap_buffers();
    }

    GuiContext::terminate();
    WindowContext::terminate();

    return 0;
}
