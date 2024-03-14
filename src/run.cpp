#include "window/window.hpp"
#include "input/input.hpp"

int main() {
    window::create_context();
    input::create_context();

    while (!window::should_close()) {
        input::poll_events();
        window::update();
        window::render();
    }

    window::terminate();

    return 0;
}
