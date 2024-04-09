#version 330 core
out vec4 FragColor;

in vec2 buildingRoofTexCoord;

uniform sampler2D texture5;

void main()
{
	FragColor = texture(texture5, buildingRoofTexCoord);
}