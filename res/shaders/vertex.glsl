#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 texture_uv_index;
layout (location = 2) in vec3 offset;
layout (location = 3) in int face;

uniform mat4 u_camera;

out vec3 texture_coordinate;

const vec3 texture_uvs[4] = vec3[4](
    vec3(0, 0, 0),
    vec3(0, 1, 0),
    vec3(1, 0, 0),
    vec3(1, 1, 0)
);

vec3 face_offsets[6] = vec3[6](
    vec3(0 + position.x, 0 + position.y, 0 + position.z),
    vec3(1 + position.x, 0 + position.y, 1 - position.z),
    vec3(0 + position.z, 0 + position.x, 0 + position.y),
    vec3(0 + position.z, 1 + position.x, 1 - position.y),
    vec3(1 - position.z, 0 + position.y, 0 + position.x),
    vec3(0 + position.z, 0 + position.y, 1 + position.x)
);

void main() {
    vec3 new_position = face_offsets[face];
    vec3 offset_position = vec3(new_position.x + offset.x, new_position.y + offset.y, new_position.z + offset.z);
    gl_Position = u_camera * vec4(offset_position, position.w);
    texture_coordinate = texture_uv_index;
}
