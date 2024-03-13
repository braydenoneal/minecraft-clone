#version 330 core

layout (location = 0) out vec4 color;

in float f_Brightness;
in vec3 v_texture_coordinates;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, v_texture_coordinates);
    color = texture_color * f_Brightness;
}
