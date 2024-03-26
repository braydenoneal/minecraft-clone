#include "render.hpp"

namespace render {
    void create_context() {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void clear_screen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(166.0f / 255.0f, 208.0f / 255.0f, 1.0f, 1.0f);
    }
}
