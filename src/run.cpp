#include "window/window.hpp"
#include "input/input.hpp"

int main() {
    window::create_context();
    input::create_context();

    while (!window::should_close()) {
        input::get_input();
        input::update_game_state();
        window::render();
    }

    window::terminate();

    return 0;
}
