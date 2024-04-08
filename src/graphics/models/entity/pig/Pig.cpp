#include "Pig.hpp"

Pig::Pig() {
    shader.setShaders("../res/shaders/entity/vertex.glsl",
                      "../res/shaders/entity/fragment.glsl");
    shader.bind();

    texture.setTextures({"../res/textures/entity/pig.png"}, 64, 32);
    texture.bind();

    shader.setUniform1i("u_textures", 0);

    leg_front_right = {
            {-0.4375, 0.0, -0.3125, 4, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.3125, 4, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.0625, 8, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.0625, 8, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.0625, 8, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.3125, 4, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.0625, 12, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.0625, 12, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.3125, 16, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.3125, 16, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.3125, 16, 6, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.0625, 12, 12, 0, 0.8, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.3125, 8, 16, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.3125, 8, 12, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.0625, 12, 16, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.0625, 12, 12, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.0625, 12, 16, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.3125, 8, 12, 0, 0.4, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.3125, 8, 16, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.3125, 8, 12, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.0625, 4, 16, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.0625, 4, 12, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.0625, 4, 16, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.3125, 8, 12, 0, 1, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.3125, 0, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.3125, 0, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.3125, 4, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.3125, 4, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.3125, 4, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.3125, 0, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.0, -0.0625, 8, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.0625, 8, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.0625, 12, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.375, -0.0625, 12, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.1875, 0.0, -0.0625, 12, 6, 0, 0.6, -0.3125, 0.375, -0.1875},
            {-0.4375, 0.375, -0.0625, 8, 12, 0, 0.6, -0.3125, 0.375, -0.1875},
    };

    leg_front_left = {
            {-0.4375, 0.0, 0.0625, 4, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.0625, 4, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.3125, 8, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.3125, 8, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.3125, 8, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.0625, 4, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.3125, 12, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.3125, 12, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.0625, 16, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.0625, 16, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.0625, 16, 6, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.3125, 12, 12, 0, 0.8, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.0625, 8, 16, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.0625, 8, 12, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.3125, 12, 16, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.3125, 12, 12, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.3125, 12, 16, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.0625, 8, 12, 0, 0.4, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.0625, 8, 16, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.0625, 8, 12, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.3125, 4, 16, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.3125, 4, 12, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.3125, 4, 16, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.0625, 8, 12, 0, 1, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.0625, 0, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.0625, 0, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.0625, 4, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.0625, 4, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.0625, 4, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.0625, 0, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.0, 0.3125, 8, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.3125, 8, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.3125, 12, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.375, 0.3125, 12, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.1875, 0.0, 0.3125, 12, 6, 0, 0.6, -0.3125, 0.375, 0.1875},
            {-0.4375, 0.375, 0.3125, 8, 12, 0, 0.6, -0.3125, 0.375, 0.1875},
    };

    body = {
            {-0.5, 0.375, -0.3125, 36, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, -0.3125, 36, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, 0.3125, 46, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, 0.3125, 46, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, 0.3125, 46, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, -0.3125, 36, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.375, 0.3125, 46, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.875, 0.3125, 46, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.375, -0.3125, 56, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.875, -0.3125, 56, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.375, -0.3125, 56, 16, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.875, 0.3125, 46, 24, 0, 0.8, 0.0, 0.5625, 0.0},
            {0.5, 0.375, -0.3125, 36, 16, 0, 0.4, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, -0.3125, 36, 0, 0, 0.4, 0.0, 0.5625, 0.0},
            {0.5, 0.375, 0.3125, 46, 16, 0, 0.4, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, 0.3125, 46, 0, 0, 0.4, 0.0, 0.5625, 0.0},
            {0.5, 0.375, 0.3125, 46, 16, 0, 0.4, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, -0.3125, 36, 0, 0, 0.4, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, -0.3125, 64, 16, 0, 1, 0.0, 0.5625, 0.0},
            {0.5, 0.875, -0.3125, 64, 0, 0, 1, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, 0.3125, 54, 16, 0, 1, 0.0, 0.5625, 0.0},
            {0.5, 0.875, 0.3125, 54, 0, 0, 1, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, 0.3125, 54, 16, 0, 1, 0.0, 0.5625, 0.0},
            {0.5, 0.875, -0.3125, 64, 0, 0, 1, 0.0, 0.5625, 0.0},
            {0.5, 0.375, -0.3125, 46, 16, 0, 0.6, 0.0, 0.5625, 0.0},
            {0.5, 0.875, -0.3125, 54, 16, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, -0.3125, 46, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, -0.3125, 54, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, -0.3125, 46, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {0.5, 0.875, -0.3125, 54, 16, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.375, 0.3125, 36, 16, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, 0.3125, 28, 16, 0, 0.6, 0.0, 0.5625, 0.0},
            {0.5, 0.375, 0.3125, 36, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {0.5, 0.875, 0.3125, 28, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {0.5, 0.375, 0.3125, 36, 0, 0, 0.6, 0.0, 0.5625, 0.0},
            {-0.5, 0.875, 0.3125, 28, 16, 0, 0.6, 0.0, 0.5625, 0.0},
    };

    head = {
            {-0.875, 0.5, -0.25, 8, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 1.0, -0.25, 8, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5, 0.25, 16, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 1.0, 0.25, 16, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5, 0.25, 16, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 1.0, -0.25, 8, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 0.5, 0.25, 24, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 1.0, 0.25, 24, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 0.5, -0.25, 32, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 1.0, -0.25, 32, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 0.5, -0.25, 32, 16, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 1.0, 0.25, 24, 24, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.375, 0.5, -0.25, 16, 24, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 0.5, -0.25, 16, 32, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.375, 0.5, 0.25, 24, 24, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 0.5, 0.25, 24, 32, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.375, 0.5, 0.25, 24, 24, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 0.5, -0.25, 16, 32, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 1.0, -0.25, 8, 24, 0, 1, -0.375, 0.75, 0.0},
            {-0.375, 1.0, -0.25, 8, 32, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 1.0, 0.25, 16, 24, 0, 1, -0.375, 0.75, 0.0},
            {-0.375, 1.0, 0.25, 16, 32, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 1.0, 0.25, 16, 24, 0, 1, -0.375, 0.75, 0.0},
            {-0.375, 1.0, -0.25, 8, 32, 0, 1, -0.375, 0.75, 0.0},
            {-0.375, 0.5, -0.25, 0, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.375, 1.0, -0.25, 0, 24, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.5, -0.25, 8, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 1.0, -0.25, 8, 24, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.5, -0.25, 8, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.375, 1.0, -0.25, 0, 24, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.5, 0.25, 16, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 1.0, 0.25, 16, 24, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.375, 0.5, 0.25, 24, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.375, 1.0, 0.25, 24, 24, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.375, 0.5, 0.25, 24, 16, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 1.0, 0.25, 16, 24, 0, 0.6, -0.375, 0.75, 0.0},

            {-0.9375, 0.5625, -0.125, 17, 12, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, -0.125, 17, 15, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, 0.125, 21, 12, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, 0.125, 21, 15, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, 0.125, 21, 12, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, -0.125, 17, 15, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, 0.125, 10, 17, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.75, 0.125, 10, 20, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, -0.125, 14, 17, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.75, -0.125, 14, 20, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, -0.125, 14, 17, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.75, 0.125, 10, 20, 0, 0.8, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, -0.125, 21, 16, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, -0.125, 21, 15, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, 0.125, 25, 16, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, 0.125, 25, 15, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, 0.125, 25, 16, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, -0.125, 21, 15, 0, 0.4, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, -0.125, 21, 16, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 0.75, -0.125, 21, 15, 0, 1, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, 0.125, 17, 16, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 0.75, 0.125, 17, 15, 0, 1, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, 0.125, 17, 16, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 0.75, -0.125, 21, 15, 0, 1, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, -0.125, 16, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.75, -0.125, 16, 15, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, -0.125, 17, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, -0.125, 17, 15, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, -0.125, 17, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.75, -0.125, 16, 15, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.5625, 0.125, 21, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, 0.125, 21, 15, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, 0.125, 22, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.75, 0.125, 22, 15, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.875, 0.5625, 0.125, 22, 12, 0, 0.6, -0.375, 0.75, 0.0},
            {-0.9375, 0.75, 0.125, 21, 15, 0, 0.6, -0.375, 0.75, 0.0},
    };

    leg_back_left = {
            {0.3125, 0.0, 0.0625, 4, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.0625, 4, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.3125, 8, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.3125, 8, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.3125, 8, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.0625, 4, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.3125, 12, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.3125, 12, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.0625, 16, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.0625, 16, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.0625, 16, 6, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.3125, 12, 12, 0, 0.8, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.0625, 8, 16, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.0625, 8, 12, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.3125, 12, 16, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.3125, 12, 12, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.3125, 12, 16, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.0625, 8, 12, 0, 0.4, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.0625, 8, 16, 0, 1, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.0625, 8, 12, 0, 1, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.3125, 4, 16, 0, 1, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.3125, 4, 12, 0, 1, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.3125, 4, 16, 0, 1, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.0625, 8, 12, 0, 1, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.0625, 0, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.0625, 0, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.0625, 4, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.0625, 4, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.0625, 4, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.0625, 0, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.0, 0.3125, 8, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.3125, 8, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.3125, 12, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.5625, 0.375, 0.3125, 12, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.5625, 0.0, 0.3125, 12, 6, 0, 0.6, 0.4375, 0.375, 0.1875},
            {0.3125, 0.375, 0.3125, 8, 12, 0, 0.6, 0.4375, 0.375, 0.1875},
    };

    leg_back_right = {
            {0.3125, 0.0, -0.3125, 4, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.3125, 4, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.0625, 8, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.0625, 8, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.0625, 8, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.3125, 4, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.0625, 12, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.0625, 12, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.3125, 16, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.3125, 16, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.3125, 16, 6, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.0625, 12, 12, 0, 0.8, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.3125, 8, 16, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.3125, 8, 12, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.0625, 12, 16, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.0625, 12, 12, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.0625, 12, 16, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.3125, 8, 12, 0, 0.4, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.3125, 8, 16, 0, 1, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.3125, 8, 12, 0, 1, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.0625, 4, 16, 0, 1, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.0625, 4, 12, 0, 1, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.0625, 4, 16, 0, 1, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.3125, 8, 12, 0, 1, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.3125, 0, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.3125, 0, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.3125, 4, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.3125, 4, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.3125, 4, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.3125, 0, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.0, -0.0625, 8, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.0625, 8, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.0625, 12, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.5625, 0.375, -0.0625, 12, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.5625, 0.0, -0.0625, 12, 6, 0, 0.6, 0.4375, 0.375, -0.1875},
            {0.3125, 0.375, -0.0625, 8, 12, 0, 0.6, 0.4375, 0.375, -0.1875},
    };

    vertex_array.addAttributes(vertex_buffer, {{3, GL_FLOAT, GL_FALSE}, {3, GL_FLOAT, GL_FALSE},
                                               {1, GL_FLOAT, GL_FALSE}, {3, GL_FLOAT, GL_FALSE},
                                               {3, GL_FLOAT, GL_FALSE}}, 0);
}

void Pig::draw() {
    std::vector<PigVertex> vertex_buffer_data{};

    vertex_buffer_data.insert(vertex_buffer_data.begin(), leg_back_right.begin(), leg_back_right.end());
    vertex_buffer_data.insert(vertex_buffer_data.begin(), leg_back_left.begin(), leg_back_left.end());
    vertex_buffer_data.insert(vertex_buffer_data.begin(), leg_front_right.begin(), leg_front_right.end());
    vertex_buffer_data.insert(vertex_buffer_data.begin(), leg_front_left.begin(), leg_front_left.end());
    vertex_buffer_data.insert(vertex_buffer_data.begin(), body.begin(), body.end());
    vertex_buffer_data.insert(vertex_buffer_data.begin(), head.begin(), head.end());

    vertex_count = (GLsizei) vertex_buffer_data.size();

    vertex_buffer.setData((GLsizeiptr) (vertex_buffer_data.size() * sizeof(PigVertex)), &vertex_buffer_data[0]);

    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

void Pig::setUniforms(float aspect_ratio, glm::vec3 camera_position, glm::vec3 camera_angle, glm::vec3 position, glm::vec3 rotation) const {
    glm::mat4 perspective = glm::perspective(glm::radians(70.0f), aspect_ratio, 0.05f, 2048.0f);

    auto camera_rotate = glm::mat4(1.0f);

    camera_rotate = glm::rotate(camera_rotate, -camera_angle.x, glm::vec3(1.0f, 0.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.y, glm::vec3(0.0f, 1.0f, 0.0f));
    camera_rotate = glm::rotate(camera_rotate, -camera_angle.z, glm::vec3(0.0f, 0.0f, 1.0f));

    auto model_rotate = glm::mat4(1.0f);

    model_rotate = glm::rotate(model_rotate, -rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model_rotate = glm::rotate(model_rotate, -rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model_rotate = glm::rotate(model_rotate, -rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 camera_translate = glm::translate(glm::mat4(1.0f), -camera_position);
    glm::mat4 model_translate = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 camera_matrix = perspective * camera_rotate * camera_translate * model_translate * model_rotate;

    shader.setUniformMatrix4fv("u_camera", &camera_matrix[0][0]);
}

void Pig::setLegBackRightRotation(float x, float y, float z) {
    for (auto &vertex: leg_back_right) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}

void Pig::setLegBackLeftRotation(float x, float y, float z) {
    for (auto &vertex: leg_back_left) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}

void Pig::setLegFrontRightRotation(float x, float y, float z) {
    for (auto &vertex: leg_front_right) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}

void Pig::setLegFrontLeftRotation(float x, float y, float z) {
    for (auto &vertex: leg_front_left) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}

void Pig::setBodyRotation(float x, float y, float z) {
    for (auto &vertex: body) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}

void Pig::setHeadRotation(float x, float y, float z) {
    for (auto &vertex: head) {
        vertex.rx = x;
        vertex.ry = y;
        vertex.rz = z;
    }
}