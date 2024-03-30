#include "Texture.hpp"

Texture::Texture() {
    glGenTextures(1, &id);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::setTextures(const std::vector<std::string> &file_paths, GLint width, GLint height) const {
    bind();

    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, (int) file_paths.size(), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    unsigned char *local_buffer;

    int current_width;
    int current_height;
    int current_bits_per_pixel;

    stbi_set_flip_vertically_on_load(1);

    for (int i = 0; i < file_paths.size(); i++) {
        local_buffer = stbi_load(
            file_paths[i].c_str(),
            &current_width,
            &current_height,
            &current_bits_per_pixel,
            4
        );

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0, 0, 0, i,
            current_width,
            current_height,
            1,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            local_buffer
        );
    }

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unbind();

    if (local_buffer) {
        stbi_image_free(local_buffer);
    }
}

void Texture::bind() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
