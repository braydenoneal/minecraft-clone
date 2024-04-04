#version 330 core

layout (location = 0) out vec4 color;

void main() {
    float fog_distance = gl_FragCoord.z / gl_FragCoord.w;
    color = mix(vec4(121.0f / 255.0f, 166.0f / 255.0f, 1.0f, 1.0f), vec4(178.0f / 255.0f, 206.0f / 255.0f, 1.0f, 1.0f),
        (1.0 - exp2(-0.00000005 * fog_distance * fog_distance * fog_distance * fog_distance * fog_distance)));
}
