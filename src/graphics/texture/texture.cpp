#include "texture.hpp"

namespace texture {
    GLuint create_textures(const std::vector<std::string> &texture_file_paths, GLint texture_width, GLint texture_height) {
        stbi_set_flip_vertically_on_load(1);

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, texture_width);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, texture_width, texture_height, (int) texture_file_paths.size(), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        unsigned char *local_buffer;

        int buffer_texture_width;
        int buffer_texture_height;
        int buffer_texture_bbp;

        for (int i = 0; i < texture_file_paths.size(); i++) {
            local_buffer = stbi_load(
                texture_file_paths[i].c_str(),
                &buffer_texture_width,
                &buffer_texture_height,
                &buffer_texture_bbp,
                4
            );

            glTexSubImage3D(
                GL_TEXTURE_2D_ARRAY,
                0, 0, 0, i,
                buffer_texture_width,
                buffer_texture_height,
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

        return texture_id;
    }

    void bind(GLuint texture_id) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D_ARRAY, texture_id);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    }

    void destroy(GLuint texture_id) {
        const GLuint textures = {texture_id};

        glDeleteTextures(1, &textures);
    }
}
