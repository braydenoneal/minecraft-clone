#version 330 core

layout (location = 0) in vec2 position;

uniform float u_aspect_ratio;
uniform float u_width;

void main() {
    gl_Position.xy = vec2(position.x, position.y * u_aspect_ratio) / u_width * 2;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0f;
}
