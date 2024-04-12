#version 330 core
out vec4 FragColor;

in vec2 buildingRoofTexCoord;

uniform sampler2D texture1;

void main()
{
	vec4 texColor = texture(texture1, buildingRoofTexCoord);
	if (texColor.b < 0.05) {
	    discard;
	}
	FragColor = texColor;
}