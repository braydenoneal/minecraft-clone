#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 texture_uv;
layout (location = 2) in float brightness;

uniform mat4 u_camera;

out vec3 texture_coordinate;
out float texture_brightness;

void main() {
    gl_Position = u_camera * (position + vec4(0, 16, 0, 0));
    texture_coordinate = texture_uv;
    texture_brightness = brightness;
}
