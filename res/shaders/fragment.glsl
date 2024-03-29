#version 330 core

layout (location = 0) out vec4 color;

in vec2 texture_coordinate;
in float texture_index;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, vec3(texture_coordinate, texture_index));
    color = texture_color;
}
