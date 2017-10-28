#version 400

in vec3 position;
in vec3 interpColor;
in vec2 texCoordOut;

out vec4 fragColor;
out vec4 fragColor2;

uniform sampler2D texture;
uniform sampler2D texture2;

void main()
{
	fragColor = texture(texture, texCoordOut) * texture(texture2, texCoordOut * vec2(1.0, -1.0)) * vec4(interpColor, 1.0f);
}