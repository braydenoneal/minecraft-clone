#version 330 core

layout (location = 0) out vec4 color;

in vec2 texture_coordinate;
in float texture_index;
in float brightness;
in float occlusion_value;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, vec3(texture_coordinate, texture_index));
    texture_color.rgb *= 1.0f - (occlusion_value * 0.15f);
    texture_color.rgb *= brightness;
    float fog_distance = gl_FragCoord.z / gl_FragCoord.w;
    texture_color = mix(texture_color, vec4(121.0f / 255.0f, 166.0f / 255.0f, 1.0f, 1.0f),
        (1.0 - exp2(-0.00000000005 * fog_distance * fog_distance * fog_distance * fog_distance * fog_distance)));
    color = texture_color;
}
