#version 330 core

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform vec4 PickingColor;
uniform vec4 colorModifier;

void main(){

    color = PickingColor * colorModifier;
}