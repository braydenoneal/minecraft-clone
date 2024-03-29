#include <glad/glad.h>
#include <vector>
#include <string>
#include <stb_image.h>

class Texture {
public:
    Texture();

    void setTextures(const std::vector<std::string> &file_paths, GLint width, GLint height) const;

    void bind() const;

    static void unbind();

    ~Texture();

private:
    GLuint id{};
};
