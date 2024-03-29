#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 texture_uv_index;
layout (location = 2) in vec3 offset;

uniform mat4 u_camera;

out vec3 texture_coordinate;

const vec3 texture_uvs[4] = vec3[4](
    vec3(0, 0, 0),
    vec3(0, 1, 0),
    vec3(1, 0, 0),
    vec3(1, 1, 0)
);

void main() {
    texture_coordinate = texture_uv_index;
    gl_Position = u_camera * vec4(position.x + offset.x, position.y + offset.y, position.z + offset.z, position.w);
}
