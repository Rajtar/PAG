#version 400

in vec3 position;
in vec3 interpColor;
out vec4 fragColor;

void main()
{
	fragColor = vec4(interpColor, 1.0f);
}