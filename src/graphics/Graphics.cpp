#include "Graphics.hpp"

Graphics::Graphics() {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Graphics::clearScreen() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(clearScreenColor.r, clearScreenColor.g, clearScreenColor.b, 1.0f);
}

void Graphics::resizeViewport(int width, int height) {
    glViewport(0, 0, width, height);
}
