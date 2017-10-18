#version 400

in vec3 position;
in vec3 interpColor;
in vec2 texCoordOut;
out vec4 fragColor;

uniform sampler2D bricksTexture;

void main()
{
	//fragColor = vec4(interpColor, 1.0f);
	fragColor = texture(bricksTexture, texCoordOut);
}