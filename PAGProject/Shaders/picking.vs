#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 aPos;

// Values that stay constant for the whole mesh.
uniform mat4 wvp;
uniform mat4 model;
uniform mat4 transform;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position = wvp * transform * vec4(aPos, 1.0);

}