#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec4 PositionW;
out vec2 TexCoords;
out vec3 NormalW;

uniform mat4 wvp;
uniform mat4 model;
uniform mat4 transform;

void main()
{
    TexCoords = aTexCoords;
    NormalW = aNormal;
    PositionW = model * vec4(aPos, 1.0);

    gl_Position = wvp * transform * vec4(aPos, 1.0);
}