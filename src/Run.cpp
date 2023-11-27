#include "Window.h"
#include "Input.h"
#include "Physics.h"
#include "Matter.h"

int main() {
    Window::create_context();
    Input::create_context();
    Physics::create_context();
    Matter::create_context();

    while (!Window::should_close()) {
        Input::poll_events();
        Window::update();
        Window::render();
    }

    Window::terminate();

    return 0;
}
