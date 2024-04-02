#version 330 core
out vec4 FragColor;

uniform vec3 buildingBaseColor;

void main()
{
	FragColor = vec4(buildingBaseColor, 1.0f);
}