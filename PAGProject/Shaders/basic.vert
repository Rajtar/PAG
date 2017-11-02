#version 400

layout (location = 0) in vec3 vertexPosition;
//layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoordIn;

//out vec3 interpColor;
out vec2 texCoordOut;

uniform mat4 wvp;
uniform mat4 transform;

void main()
{
	//interpColor = vertexColor;
	texCoordOut = texCoordIn;

	gl_Position = wvp * transform * vec4(vertexPosition, 1.0f);
}