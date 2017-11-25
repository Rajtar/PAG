#version 400
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 wvp;
uniform mat4 transform;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = wvp * transform * vec4(aPos, 1.0);
}