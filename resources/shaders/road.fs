#version 330 core
out vec4 FragColor;

in vec2 roadTexCoord;

uniform sampler2D texture3;

void main()
{
	FragColor = texture(texture3, roadTexCoord);
}