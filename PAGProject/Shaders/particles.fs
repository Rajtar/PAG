#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 particlecolor;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

uniform float alphaChannel;

void main(){
	// Output color = color of the texture at the specified UV
	color = texture2D( myTextureSampler, UV ) * vec4(1.0, 1.0, 1.0, alphaChannel);// * particlecolor;

}