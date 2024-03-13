#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 texture_coordinates;
layout (location = 2) in float brightness;

out float f_Brightness;
out vec3 v_texture_coordinates;

uniform mat4 u_camera;

void main() {
    v_texture_coordinates = texture_coordinates;
    gl_Position = u_camera * position;
    f_Brightness = brightness;
}
