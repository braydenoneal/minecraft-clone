#version 330 core

layout (location = 0) out vec4 color;

in vec3 fog_position;

void main() {
    float dist = sqrt(pow(fog_position.x, 2) + pow(fog_position.y, 2) + pow(fog_position.z, 2));
    float start = 1;
    float scale = 3;
    float factor = (clamp(dist, start, start + scale) - start) / scale;
    color = mix(vec4(121.0f / 255.0f, 166.0f / 255.0f, 1.0f, 1.0f),
                vec4(178.0f / 255.0f, 206.0f / 255.0f, 1.0f, 1.0f), factor);
}
