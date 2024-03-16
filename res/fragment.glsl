#version 330 core

layout (location = 0) out vec4 color;

in float f_Brightness;
in vec3 v_texture_coordinates;

uniform sampler2DArray u_textures;

void main() {
    vec4 texture_color = texture(u_textures, v_texture_coordinates);
    float fog_distance = gl_FragCoord.z / gl_FragCoord.w;
    texture_color *= f_Brightness;
//    texture_color = mix(texture_color, vec4(138.0f / 255.0f, 163.0f / 255.0f, 1.0f, 1.0f), (1.0 - exp2(-0.0005 * fog_distance * fog_distance)));
    color = texture_color;
}
