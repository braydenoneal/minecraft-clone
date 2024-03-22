#include "window/window.hpp"

int main() {
    window::create_context();

    while (!window::should_close()) {
        window::clear_screen();
        window::next_frame();
    }

    window::terminate();

    return 0;
}
