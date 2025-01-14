#version 330 core

layout (location = 0) out vec4 color;

in vec2 texture_coordinate;
in float texture_index;
in float brightness;
in float occlusion_value;
in vec3 fog_position;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, vec3(texture_coordinate, texture_index));
    texture_color.rgb *= 1.0f - (occlusion_value * 0.2f);
    texture_color.rgb *= brightness;
    float dist = sqrt(pow(fog_position.x, 2) + pow(0, 2) + pow(fog_position.z, 2));
    float start = 16 * 10;
    float scale = 16;
    float factor = (clamp(dist, start, start + scale) - start) / scale;
    texture_color = mix(texture_color, vec4(178.0f / 255.0f, 206.0f / 255.0f, 1.0f, 1.0f), factor);
    color = texture_color;
}
