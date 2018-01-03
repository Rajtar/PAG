#version 400
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform vec4 colorModifier;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords) * colorModifier;
}