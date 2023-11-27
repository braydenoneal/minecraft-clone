#include "window.hpp"
#include "input.hpp"
#include "physics.hpp"
#include "matter.hpp"

int main() {
    window::create_context();
    input::create_context();
    physics::create_context();
    matter::create_context();

    while (!window::should_close()) {
        input::poll_events();
        window::update();
        window::render();
    }

    window::terminate();

    return 0;
}
