#version 330 core

layout (location = 0) out vec4 color;

in vec3 texture_coordinate;
in float texture_brightness;

uniform sampler2DArray u_textures;

void main() {
    color = texture(u_textures, vec3(texture_coordinate.x / 64, texture_coordinate.y / 32, texture_coordinate.z));
    color.rgb *= texture_brightness;
}
