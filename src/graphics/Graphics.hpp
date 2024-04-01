#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class Graphics {
public:
    Graphics();

    void clearScreen() const;

    static void resizeViewport(int width, int height) ;

private:
    glm::vec3 clearScreenColor{121.0f / 255.0f, 166.0f / 255.0f, 1.0f};
};
