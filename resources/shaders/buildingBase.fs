#version 330 core
out vec4 FragColor;

in vec2 buildingBaseTexCoord;

uniform sampler2D texture4;

void main()
{
	FragColor = texture(texture4, buildingBaseTexCoord);
}