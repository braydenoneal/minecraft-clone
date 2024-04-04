#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Graphics {
public:
    Graphics();

    void clearScreen() const;

    static void resizeViewport(int width, int height) ;

private:
    glm::vec3 clearScreenColor{178.0f / 255.0f, 206.0f / 255.0f, 1.0f};
};
