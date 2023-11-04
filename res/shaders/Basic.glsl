// shader vertex
#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 textureCoordinates;
layout (location = 2) in float brightness;

out vec3 v_TextureCoordinates;
out float f_Brightness;

//uniform mat4 u_cr;
//uniform mat4 u_ct;
//uniform mat4 u_mr;
uniform mat4 u_mt;
//uniform mat4 u_p;
uniform mat4 u_all;

void main() {
    gl_Position = u_all * u_mt * position;
    v_TextureCoordinates = textureCoordinates;
    f_Brightness = brightness;
}

// shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec3 v_TextureCoordinates;
in float f_Brightness;

uniform sampler2DArray u_Textures;

void main() {
    vec4 textureColor = texture(u_Textures, v_TextureCoordinates);
    textureColor.rgb *= f_Brightness;
    color = textureColor;
}
