#include "Pig.hpp"

Pig::Pig() {
    shader.setShaders("../res/shaders/entity/vertex.glsl",
                      "../res/shaders/entity/fragment.glsl");
    shader.bind();

    texture.setTextures({"../res/textures/entity/pig.png"}, 64, 32);
    texture.bind();

    shader.setUniform1i("u_textures", 0);

    std::vector<PigVertex> vertex_buffer_data = {
            {0.0, 0.0, 0.1875, 4, 6, 0, 0.8},
            {0.0, 0.375, 0.1875, 4, 12, 0, 0.8},
            {0.0, 0.0, 0.4375, 8, 6, 0, 0.8},
            {0.0, 0.375, 0.4375, 8, 12, 0, 0.8},
            {0.0, 0.0, 0.4375, 8, 6, 0, 0.8},
            {0.0, 0.375, 0.1875, 4, 12, 0, 0.8},
            {0.25, 0.0, 0.4375, 12, 6, 0, 0.8},
            {0.25, 0.375, 0.4375, 12, 12, 0, 0.8},
            {0.25, 0.0, 0.1875, 16, 6, 0, 0.8},
            {0.25, 0.375, 0.1875, 16, 12, 0, 0.8},
            {0.25, 0.0, 0.1875, 16, 6, 0, 0.8},
            {0.25, 0.375, 0.4375, 12, 12, 0, 0.8},
            {0.25, 0.0, 0.1875, 8, 16, 0, 0.4},
            {0.0, 0.0, 0.1875, 8, 12, 0, 0.4},
            {0.25, 0.0, 0.4375, 12, 16, 0, 0.4},
            {0.0, 0.0, 0.4375, 12, 12, 0, 0.4},
            {0.25, 0.0, 0.4375, 12, 16, 0, 0.4},
            {0.0, 0.0, 0.1875, 8, 12, 0, 0.4},
            {0.0, 0.375, 0.1875, 8, 16, 0, 1},
            {0.25, 0.375, 0.1875, 8, 12, 0, 1},
            {0.0, 0.375, 0.4375, 4, 16, 0, 1},
            {0.25, 0.375, 0.4375, 4, 12, 0, 1},
            {0.0, 0.375, 0.4375, 4, 16, 0, 1},
            {0.25, 0.375, 0.1875, 8, 12, 0, 1},
            {0.25, 0.0, 0.1875, 0, 6, 0, 0.6},
            {0.25, 0.375, 0.1875, 0, 12, 0, 0.6},
            {0.0, 0.0, 0.1875, 4, 6, 0, 0.6},
            {0.0, 0.375, 0.1875, 4, 12, 0, 0.6},
            {0.0, 0.0, 0.1875, 4, 6, 0, 0.6},
            {0.25, 0.375, 0.1875, 0, 12, 0, 0.6},
            {0.0, 0.0, 0.4375, 8, 6, 0, 0.6},
            {0.0, 0.375, 0.4375, 8, 12, 0, 0.6},
            {0.25, 0.0, 0.4375, 12, 6, 0, 0.6},
            {0.25, 0.375, 0.4375, 12, 12, 0, 0.6},
            {0.25, 0.0, 0.4375, 12, 6, 0, 0.6},
            {0.0, 0.375, 0.4375, 8, 12, 0, 0.6},
            {0.0, 0.0, 0.5625, 4, 6, 0, 0.8},
            {0.0, 0.375, 0.5625, 4, 12, 0, 0.8},
            {0.0, 0.0, 0.8125, 8, 6, 0, 0.8},
            {0.0, 0.375, 0.8125, 8, 12, 0, 0.8},
            {0.0, 0.0, 0.8125, 8, 6, 0, 0.8},
            {0.0, 0.375, 0.5625, 4, 12, 0, 0.8},
            {0.25, 0.0, 0.8125, 12, 6, 0, 0.8},
            {0.25, 0.375, 0.8125, 12, 12, 0, 0.8},
            {0.25, 0.0, 0.5625, 16, 6, 0, 0.8},
            {0.25, 0.375, 0.5625, 16, 12, 0, 0.8},
            {0.25, 0.0, 0.5625, 16, 6, 0, 0.8},
            {0.25, 0.375, 0.8125, 12, 12, 0, 0.8},
            {0.25, 0.0, 0.5625, 8, 16, 0, 0.4},
            {0.0, 0.0, 0.5625, 8, 12, 0, 0.4},
            {0.25, 0.0, 0.8125, 12, 16, 0, 0.4},
            {0.0, 0.0, 0.8125, 12, 12, 0, 0.4},
            {0.25, 0.0, 0.8125, 12, 16, 0, 0.4},
            {0.0, 0.0, 0.5625, 8, 12, 0, 0.4},
            {0.0, 0.375, 0.5625, 8, 16, 0, 1},
            {0.25, 0.375, 0.5625, 8, 12, 0, 1},
            {0.0, 0.375, 0.8125, 4, 16, 0, 1},
            {0.25, 0.375, 0.8125, 4, 12, 0, 1},
            {0.0, 0.375, 0.8125, 4, 16, 0, 1},
            {0.25, 0.375, 0.5625, 8, 12, 0, 1},
            {0.25, 0.0, 0.5625, 0, 6, 0, 0.6},
            {0.25, 0.375, 0.5625, 0, 12, 0, 0.6},
            {0.0, 0.0, 0.5625, 4, 6, 0, 0.6},
            {0.0, 0.375, 0.5625, 4, 12, 0, 0.6},
            {0.0, 0.0, 0.5625, 4, 6, 0, 0.6},
            {0.25, 0.375, 0.5625, 0, 12, 0, 0.6},
            {0.0, 0.0, 0.8125, 8, 6, 0, 0.6},
            {0.0, 0.375, 0.8125, 8, 12, 0, 0.6},
            {0.25, 0.0, 0.8125, 12, 6, 0, 0.6},
            {0.25, 0.375, 0.8125, 12, 12, 0, 0.6},
            {0.25, 0.0, 0.8125, 12, 6, 0, 0.6},
            {0.0, 0.375, 0.8125, 8, 12, 0, 0.6},
            {-0.0625, 0.375, 0.1875, 36, 16, 0, 0.8},
            {-0.0625, 0.875, 0.1875, 36, 24, 0, 0.8},
            {-0.0625, 0.375, 0.8125, 46, 16, 0, 0.8},
            {-0.0625, 0.875, 0.8125, 46, 24, 0, 0.8},
            {-0.0625, 0.375, 0.8125, 46, 16, 0, 0.8},
            {-0.0625, 0.875, 0.1875, 36, 24, 0, 0.8},
            {0.9375, 0.375, 0.8125, 46, 16, 0, 0.8},
            {0.9375, 0.875, 0.8125, 46, 24, 0, 0.8},
            {0.9375, 0.375, 0.1875, 56, 16, 0, 0.8},
            {0.9375, 0.875, 0.1875, 56, 24, 0, 0.8},
            {0.9375, 0.375, 0.1875, 56, 16, 0, 0.8},
            {0.9375, 0.875, 0.8125, 46, 24, 0, 0.8},
            {0.9375, 0.375, 0.1875, 36, 16, 0, 0.4},
            {-0.0625, 0.375, 0.1875, 36, 0, 0, 0.4},
            {0.9375, 0.375, 0.8125, 46, 16, 0, 0.4},
            {-0.0625, 0.375, 0.8125, 46, 0, 0, 0.4},
            {0.9375, 0.375, 0.8125, 46, 16, 0, 0.4},
            {-0.0625, 0.375, 0.1875, 36, 0, 0, 0.4},
            {-0.0625, 0.875, 0.1875, 64, 16, 0, 1},
            {0.9375, 0.875, 0.1875, 64, 0, 0, 1},
            {-0.0625, 0.875, 0.8125, 54, 16, 0, 1},
            {0.9375, 0.875, 0.8125, 54, 0, 0, 1},
            {-0.0625, 0.875, 0.8125, 54, 16, 0, 1},
            {0.9375, 0.875, 0.1875, 64, 0, 0, 1},
            {0.9375, 0.375, 0.1875, 46, 16, 0, 0.6},
            {0.9375, 0.875, 0.1875, 54, 16, 0, 0.6},
            {-0.0625, 0.375, 0.1875, 46, 0, 0, 0.6},
            {-0.0625, 0.875, 0.1875, 54, 0, 0, 0.6},
            {-0.0625, 0.375, 0.1875, 46, 0, 0, 0.6},
            {0.9375, 0.875, 0.1875, 54, 16, 0, 0.6},
            {-0.0625, 0.375, 0.8125, 36, 16, 0, 0.6},
            {-0.0625, 0.875, 0.8125, 28, 16, 0, 0.6},
            {0.9375, 0.375, 0.8125, 36, 0, 0, 0.6},
            {0.9375, 0.875, 0.8125, 28, 0, 0, 0.6},
            {0.9375, 0.375, 0.8125, 36, 0, 0, 0.6},
            {-0.0625, 0.875, 0.8125, 28, 16, 0, 0.6},
            {-0.4375, 0.5, 0.25, 8, 16, 0, 0.8},
            {-0.4375, 1.0, 0.25, 8, 24, 0, 0.8},
            {-0.4375, 0.5, 0.75, 16, 16, 0, 0.8},
            {-0.4375, 1.0, 0.75, 16, 24, 0, 0.8},
            {-0.4375, 0.5, 0.75, 16, 16, 0, 0.8},
            {-0.4375, 1.0, 0.25, 8, 24, 0, 0.8},
            {0.0625, 0.5, 0.75, 24, 16, 0, 0.8},
            {0.0625, 1.0, 0.75, 24, 24, 0, 0.8},
            {0.0625, 0.5, 0.25, 32, 16, 0, 0.8},
            {0.0625, 1.0, 0.25, 32, 24, 0, 0.8},
            {0.0625, 0.5, 0.25, 32, 16, 0, 0.8},
            {0.0625, 1.0, 0.75, 24, 24, 0, 0.8},
            {0.0625, 0.5, 0.25, 16, 24, 0, 0.4},
            {-0.4375, 0.5, 0.25, 16, 32, 0, 0.4},
            {0.0625, 0.5, 0.75, 24, 24, 0, 0.4},
            {-0.4375, 0.5, 0.75, 24, 32, 0, 0.4},
            {0.0625, 0.5, 0.75, 24, 24, 0, 0.4},
            {-0.4375, 0.5, 0.25, 16, 32, 0, 0.4},
            {-0.4375, 1.0, 0.25, 8, 24, 0, 1},
            {0.0625, 1.0, 0.25, 8, 32, 0, 1},
            {-0.4375, 1.0, 0.75, 16, 24, 0, 1},
            {0.0625, 1.0, 0.75, 16, 32, 0, 1},
            {-0.4375, 1.0, 0.75, 16, 24, 0, 1},
            {0.0625, 1.0, 0.25, 8, 32, 0, 1},
            {0.0625, 0.5, 0.25, 0, 16, 0, 0.6},
            {0.0625, 1.0, 0.25, 0, 24, 0, 0.6},
            {-0.4375, 0.5, 0.25, 8, 16, 0, 0.6},
            {-0.4375, 1.0, 0.25, 8, 24, 0, 0.6},
            {-0.4375, 0.5, 0.25, 8, 16, 0, 0.6},
            {0.0625, 1.0, 0.25, 0, 24, 0, 0.6},
            {-0.4375, 0.5, 0.75, 16, 16, 0, 0.6},
            {-0.4375, 1.0, 0.75, 16, 24, 0, 0.6},
            {0.0625, 0.5, 0.75, 24, 16, 0, 0.6},
            {0.0625, 1.0, 0.75, 24, 24, 0, 0.6},
            {0.0625, 0.5, 0.75, 24, 16, 0, 0.6},
            {-0.4375, 1.0, 0.75, 16, 24, 0, 0.6},
            {-0.5, 0.5625, 0.375, 17, 12, 0, 0.8},
            {-0.5, 0.75, 0.375, 17, 15, 0, 0.8},
            {-0.5, 0.5625, 0.625, 21, 12, 0, 0.8},
            {-0.5, 0.75, 0.625, 21, 15, 0, 0.8},
            {-0.5, 0.5625, 0.625, 21, 12, 0, 0.8},
            {-0.5, 0.75, 0.375, 17, 15, 0, 0.8},
            {-0.4375, 0.5625, 0.625, 10, 17, 0, 0.8},
            {-0.4375, 0.75, 0.625, 10, 20, 0, 0.8},
            {-0.4375, 0.5625, 0.375, 14, 17, 0, 0.8},
            {-0.4375, 0.75, 0.375, 14, 20, 0, 0.8},
            {-0.4375, 0.5625, 0.375, 14, 17, 0, 0.8},
            {-0.4375, 0.75, 0.625, 10, 20, 0, 0.8},
            {-0.4375, 0.5625, 0.375, 21, 16, 0, 0.4},
            {-0.5, 0.5625, 0.375, 21, 15, 0, 0.4},
            {-0.4375, 0.5625, 0.625, 25, 16, 0, 0.4},
            {-0.5, 0.5625, 0.625, 25, 15, 0, 0.4},
            {-0.4375, 0.5625, 0.625, 25, 16, 0, 0.4},
            {-0.5, 0.5625, 0.375, 21, 15, 0, 0.4},
            {-0.5, 0.75, 0.375, 21, 16, 0, 1},
            {-0.4375, 0.75, 0.375, 21, 15, 0, 1},
            {-0.5, 0.75, 0.625, 17, 16, 0, 1},
            {-0.4375, 0.75, 0.625, 17, 15, 0, 1},
            {-0.5, 0.75, 0.625, 17, 16, 0, 1},
            {-0.4375, 0.75, 0.375, 21, 15, 0, 1},
            {-0.4375, 0.5625, 0.375, 16, 12, 0, 0.6},
            {-0.4375, 0.75, 0.375, 16, 15, 0, 0.6},
            {-0.5, 0.5625, 0.375, 17, 12, 0, 0.6},
            {-0.5, 0.75, 0.375, 17, 15, 0, 0.6},
            {-0.5, 0.5625, 0.375, 17, 12, 0, 0.6},
            {-0.4375, 0.75, 0.375, 16, 15, 0, 0.6},
            {-0.5, 0.5625, 0.625, 21, 12, 0, 0.6},
            {-0.5, 0.75, 0.625, 21, 15, 0, 0.6},
            {-0.4375, 0.5625, 0.625, 22, 12, 0, 0.6},
            {-0.4375, 0.75, 0.625, 22, 15, 0, 0.6},
            {-0.4375, 0.5625, 0.625, 22, 12, 0, 0.6},
            {-0.5, 0.75, 0.625, 21, 15, 0, 0.6},
            {0.75, 0.0, 0.5625, 4, 6, 0, 0.8},
            {0.75, 0.375, 0.5625, 4, 12, 0, 0.8},
            {0.75, 0.0, 0.8125, 8, 6, 0, 0.8},
            {0.75, 0.375, 0.8125, 8, 12, 0, 0.8},
            {0.75, 0.0, 0.8125, 8, 6, 0, 0.8},
            {0.75, 0.375, 0.5625, 4, 12, 0, 0.8},
            {1.0, 0.0, 0.8125, 12, 6, 0, 0.8},
            {1.0, 0.375, 0.8125, 12, 12, 0, 0.8},
            {1.0, 0.0, 0.5625, 16, 6, 0, 0.8},
            {1.0, 0.375, 0.5625, 16, 12, 0, 0.8},
            {1.0, 0.0, 0.5625, 16, 6, 0, 0.8},
            {1.0, 0.375, 0.8125, 12, 12, 0, 0.8},
            {1.0, 0.0, 0.5625, 8, 16, 0, 0.4},
            {0.75, 0.0, 0.5625, 8, 12, 0, 0.4},
            {1.0, 0.0, 0.8125, 12, 16, 0, 0.4},
            {0.75, 0.0, 0.8125, 12, 12, 0, 0.4},
            {1.0, 0.0, 0.8125, 12, 16, 0, 0.4},
            {0.75, 0.0, 0.5625, 8, 12, 0, 0.4},
            {0.75, 0.375, 0.5625, 8, 16, 0, 1},
            {1.0, 0.375, 0.5625, 8, 12, 0, 1},
            {0.75, 0.375, 0.8125, 4, 16, 0, 1},
            {1.0, 0.375, 0.8125, 4, 12, 0, 1},
            {0.75, 0.375, 0.8125, 4, 16, 0, 1},
            {1.0, 0.375, 0.5625, 8, 12, 0, 1},
            {1.0, 0.0, 0.5625, 0, 6, 0, 0.6},
            {1.0, 0.375, 0.5625, 0, 12, 0, 0.6},
            {0.75, 0.0, 0.5625, 4, 6, 0, 0.6},
            {0.75, 0.375, 0.5625, 4, 12, 0, 0.6},
            {0.75, 0.0, 0.5625, 4, 6, 0, 0.6},
            {1.0, 0.375, 0.5625, 0, 12, 0, 0.6},
            {0.75, 0.0, 0.8125, 8, 6, 0, 0.6},
            {0.75, 0.375, 0.8125, 8, 12, 0, 0.6},
            {1.0, 0.0, 0.8125, 12, 6, 0, 0.6},
            {1.0, 0.375, 0.8125, 12, 12, 0, 0.6},
            {1.0, 0.0, 0.8125, 12, 6, 0, 0.6},
            {0.75, 0.375, 0.8125, 8, 12, 0, 0.6},
            {0.75, 0.0, 0.1875, 4, 6, 0, 0.8},
            {0.75, 0.375, 0.1875, 4, 12, 0, 0.8},
            {0.75, 0.0, 0.4375, 8, 6, 0, 0.8},
            {0.75, 0.375, 0.4375, 8, 12, 0, 0.8},
            {0.75, 0.0, 0.4375, 8, 6, 0, 0.8},
            {0.75, 0.375, 0.1875, 4, 12, 0, 0.8},
            {1.0, 0.0, 0.4375, 12, 6, 0, 0.8},
            {1.0, 0.375, 0.4375, 12, 12, 0, 0.8},
            {1.0, 0.0, 0.1875, 16, 6, 0, 0.8},
            {1.0, 0.375, 0.1875, 16, 12, 0, 0.8},
            {1.0, 0.0, 0.1875, 16, 6, 0, 0.8},
            {1.0, 0.375, 0.4375, 12, 12, 0, 0.8},
            {1.0, 0.0, 0.1875, 8, 16, 0, 0.4},
            {0.75, 0.0, 0.1875, 8, 12, 0, 0.4},
            {1.0, 0.0, 0.4375, 12, 16, 0, 0.4},
            {0.75, 0.0, 0.4375, 12, 12, 0, 0.4},
            {1.0, 0.0, 0.4375, 12, 16, 0, 0.4},
            {0.75, 0.0, 0.1875, 8, 12, 0, 0.4},
            {0.75, 0.375, 0.1875, 8, 16, 0, 1},
            {1.0, 0.375, 0.1875, 8, 12, 0, 1},
            {0.75, 0.375, 0.4375, 4, 16, 0, 1},
            {1.0, 0.375, 0.4375, 4, 12, 0, 1},
            {0.75, 0.375, 0.4375, 4, 16, 0, 1},
            {1.0, 0.375, 0.1875, 8, 12, 0, 1},
            {1.0, 0.0, 0.1875, 0, 6, 0, 0.6},
            {1.0, 0.375, 0.1875, 0, 12, 0, 0.6},
            {0.75, 0.0, 0.1875, 4, 6, 0, 0.6},
            {0.75, 0.375, 0.1875, 4, 12, 0, 0.6},
            {0.75, 0.0, 0.1875, 4, 6, 0, 0.6},
            {1.0, 0.375, 0.1875, 0, 12, 0, 0.6},
            {0.75, 0.0, 0.4375, 8, 6, 0, 0.6},
            {0.75, 0.375, 0.4375, 8, 12, 0, 0.6},
            {1.0, 0.0, 0.4375, 12, 6, 0, 0.6},
            {1.0, 0.375, 0.4375, 12, 12, 0, 0.6},
            {1.0, 0.0, 0.4375, 12, 6, 0, 0.6},
            {0.75, 0.375, 0.4375, 8, 12, 0, 0.6},
    };

    vertex_count = (GLsizei) vertex_buffer_data.size();

    vertex_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(PigVertex)), &vertex_buffer_data[0]);

    vertex_array.addAttributes(vertex_buffer, {{3, GL_FLOAT, GL_FALSE}, {3, GL_FLOAT, GL_FALSE},
                                               {1, GL_FLOAT, GL_FALSE}}, 0);
}

void Pig::draw() const {
    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Pig::setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle) const {
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), aspect_ratio, 0.05f, 2048.0f);

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, -camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f), -camera_position);
    glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
}
