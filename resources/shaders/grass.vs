#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aGrassTexCoord;

out vec2 grassTexCoord;

uniform mat4 grassModel;
uniform mat4 grassView;
uniform mat4 grassProjection;

void main()
{
	gl_Position = grassProjection * grassView * grassModel * vec4(aPos, 1.0f);
	grassTexCoord = vec2(aGrassTexCoord.x, aGrassTexCoord.y);
}