#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;

out vec3 position;
out vec3 interpColor;

void main()
{
	position = vertexPosition;
	interpColor = vertexColor;

	gl_Position = vec4(vertexPosition, 1.0f);
}