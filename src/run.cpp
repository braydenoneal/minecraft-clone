#include "window/window.hpp"
#include "input/input.hpp"

using namespace std;

struct chunkz {
    int x;
    int z;
    int blocks[6];
};

struct region {
    unsigned long chunk_quantity;
    vector<chunkz> chunks;
};

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
