#include "texture.hpp"

namespace texture {
    GLuint create(const vector<string> &file_paths, GLint width, GLint height) {
        stbi_set_flip_vertically_on_load(1);

        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, id);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, (int) file_paths.size(), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        unsigned char *local_buffer;

        int current_width;
        int current_height;
        int current_bits_per_pixel;

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

        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

        if (local_buffer) {
            stbi_image_free(local_buffer);
        }

        return id;
    }

    void bind(GLuint id) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, id);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void destroy(GLuint id) {
        glDeleteTextures(1, &id);
    }
}
