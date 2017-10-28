#version 400

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texCoordIn;

out vec3 position;
out vec3 interpColor;
out vec2 texCoordOut;

void main()
{
	position = vertexPosition;
	interpColor = vec3(texCoordIn, 0.0f);
	texCoordOut = texCoordIn;

	gl_Position = vec4(vertexPosition, 1.0f);
}