#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 u_camera;

void main() {
    gl_Position = u_camera * position;
}
