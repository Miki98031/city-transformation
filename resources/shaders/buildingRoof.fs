#version 330 core
out vec4 FragColor;

uniform vec3 buildingRoofColor;

void main()
{
	FragColor = vec4(buildingRoofColor, 1.0f);
}