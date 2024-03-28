#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in uint texture_uv_index;

uniform mat4 u_camera;

out vec3 texture_coordinate;

vec3 texture_coordinates(uint uv) {
    switch (uv) {
        case 0:
            return vec3(0.0f, 0.0f, 0.0f);
        case 1:
            return vec3(0.0f, 1.0f, 0.0f);
        case 2:
            return vec3(1.0f, 0.0f, 0.0f);
        case 3:
            return vec3(1.0f, 1.0f, 0.0f);
        default:
            return vec3(0.0f, 0.0f, 0.0f);
    }
}

void main() {
    texture_coordinate = texture_coordinates(texture_uv_index);
    gl_Position = u_camera * position;
}
