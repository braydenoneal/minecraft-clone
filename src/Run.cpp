#include "Context.h"

int main() {
    WindowContext window_context;
    GameContext game_context;
    Input input(&window_context, &game_context);
    GuiContext gui_context(&window_context, &game_context);
    Renderer renderer(&window_context, &game_context);

    int quad_count = 6 * Chunk::size * Chunk::size;

//    std::vector<float> floats = Chunk::get_flat_chunk_vertices();
//    for (float value : floats) {
//        std::cout << value << std::endl;
//    }

//    Cube cube(quad_count, &Chunk::flat_chunk_positions()[0], &Chunk::flat_chunk_indices()[0]);
//    Cube cube(Chunk::get_chunk_vertices(Chunk::get_block_faces(Chunk::flat_chunk_blocks())).size(), Chunk::get_flat_chunk_vertices().data(), Chunk::get_flat_chunk_indices().data());
//    Cube cube(quad_count, &Chunk::flat_chunk_positions()[0], Chunk::get_indices_of_size(6 * 256).data());

//    std::vector<Cube> cubes{};
//
//    for (int x = 0; x < game_context.cube_count; x++) {
//        for (int z = 0; z < game_context.cube_count; z++) {
//            Cube cube(Chunk::get_chunk_vertices(Chunk::get_block_faces(Chunk::flat_chunk_blocks(x, z))).size(), Chunk::get_flat_chunk_vertices(x, z).data(), Chunk::get_flat_chunk_indices(x, z).data());
//            cubes.push_back(cube);
//        }
//    }

//    Draw draw(&window_context, &game_context, &cube);

    while(!window_context.window_should_close()) {
        WindowContext::handle_events();
        input.do_actions();
        renderer.render();
//        draw.draw();
//        for (Cube cube : cubes) {
//            Draw draw(&window_context, &game_context, &cube);
//            draw.draw();
//        }
        for (int x = 0; x < game_context.cube_count; x++) {
            for (int z = 0; z < game_context.cube_count; z++) {
                Cube cube(Chunk::get_chunk_vertices(Chunk::get_block_faces(Chunk::flat_chunk_blocks(x, z))).size(), Chunk::get_flat_chunk_vertices(x, z).data(), Chunk::get_flat_chunk_indices(x, z).data());
                Draw draw(&window_context, &game_context, &cube);
                draw.draw(x, z);
            }
        }
        gui_context.render();
        window_context.swap_buffers();
    }

    GuiContext::terminate();
    WindowContext::terminate();

    return 0;
}
