#version 400

//in vec3 interpColor;
in vec2 texCoordOut;
out vec4 fragColor;

uniform sampler2D texture;

void main()
{
	fragColor = texture(texture, texCoordOut);// * vec4(interpColor, 1.0f);
	//fragColor = vec4(interpColor, 1.0f);
}