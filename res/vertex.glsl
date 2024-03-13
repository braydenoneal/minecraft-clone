#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in float brightness;

uniform mat4 u_camera;

out float f_Brightness;

void main() {
    gl_Position = u_camera * position;
    f_Brightness = brightness;
}
