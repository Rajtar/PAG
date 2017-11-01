#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoordIn;

out vec3 position;
out vec3 interpColor;
out vec2 texCoordOut;

uniform mat4 wvp;

void main()
{
	position = vertexPosition;
	interpColor = vertexColor;
	texCoordOut = texCoordIn;

	gl_Position = wvp * vec4(vertexPosition, 1.0f);
}