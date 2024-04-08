#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 texture_uv;
layout (location = 2) in float brightness;
layout (location = 3) in vec3 rotate_origin;
layout (location = 4) in vec3 rotate_amount;

uniform mat4 u_camera;

out vec3 texture_coordinate;
out float texture_brightness;

mat4 rotationMatrix(vec3 axis, float angle)
{
    axis = normalize(axis);
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

void main() {
    mat4 rotx = rotationMatrix(vec3(1, 0, 0), rotate_amount.x);
    mat4 roty = rotationMatrix(vec3(0, 1, 0), rotate_amount.y);
    mat4 rotz = rotationMatrix(vec3(0, 0, 1), rotate_amount.z);
    vec4 origined_pos = vec4(position.x - rotate_origin.x, position.y - rotate_origin.y, position.z - rotate_origin.z, 1);
    vec4 rotated_position = rotx * roty * rotz * origined_pos;
    vec4 final_position = vec4(rotated_position.x + rotate_origin.x, rotated_position.y + rotate_origin.y, rotated_position.z + rotate_origin.z, 1);
    gl_Position = u_camera * (final_position);
    texture_coordinate = texture_uv;
    texture_brightness = brightness;
}
