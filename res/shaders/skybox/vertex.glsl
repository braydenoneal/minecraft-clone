#version 330 core

layout (location = 0) in vec4 position;

uniform mat4 u_camera;

out vec3 pos;

void main() {
    gl_Position = u_camera * vec4(position.x * 100, position.y + 1, position.z * 100, position.w);
    pos = vec3(position.x * 100, position.y + 1, position.z * 100);
}
