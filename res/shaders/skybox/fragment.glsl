#version 330 core

layout (location = 0) out vec4 color;

in vec3 pos;

void main() {
    float dist = sqrt(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2));
    color = mix(vec4(121.0f / 255.0f, 166.0f / 255.0f, 1.0f, 1.0f),
                vec4(178.0f / 255.0f, 206.0f / 255.0f, 1.0f, 1.0f), (1.0 - exp2(-0.05 * dist * dist * dist)));
}
