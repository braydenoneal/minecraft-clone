#version 330 core

layout (location = 0) out vec4 color;

in vec3 texture_coordinate;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, texture_coordinate);
    color = texture_color;
}
