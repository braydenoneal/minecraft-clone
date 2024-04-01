#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texture_uv_index;

layout (location = 2) in ivec3 offset;
layout (location = 3) in int face;
layout (location = 4) in int texture_index_in;
layout (location = 5) in ivec4 occlusion_value_in;

uniform mat4 u_camera;

out vec2 texture_coordinate;
out float texture_index;
out float brightness;
out float occlusion_value;

vec3 face_offsets[6] = vec3[6](
    vec3(0 + position.x, 0 + position.y, 0 + position.z),
    vec3(1 + position.x, 0 + position.y, 1 - position.z),
    vec3(0 + position.z, 0 + position.x, 0 + position.y),
    vec3(0 + position.z, 1 + position.x, 1 - position.y),
    vec3(1 - position.z, 0 + position.y, 0 + position.x),
    vec3(0 + position.z, 0 + position.y, 1 + position.x)
);

float brightnesses[6] = float[6](0.8, 0.8, 0.4, 1.0, 0.6, 0.6);

void main() {
    brightness = brightnesses[face];
    texture_index = float(texture_index_in);
    occlusion_value = float(occlusion_value_in[gl_VertexID]);
    vec3 new_position = face_offsets[face];
    vec3 offset_position = vec3(new_position.x + offset.x, new_position.y + offset.y, new_position.z + offset.z);
    gl_Position = u_camera * vec4(offset_position, position.w);
    texture_coordinate = texture_uv_index;
}
