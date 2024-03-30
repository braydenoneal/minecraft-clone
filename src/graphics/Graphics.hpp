#include <glad/glad.h>
#include <glm/glm.hpp>

class Graphics {
public:
    Graphics();

    void clearScreen() const;

private:
    glm::vec3 clearScreenColor{};
};
