#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCobblestoneTexCoord;

out vec2 cobblestoneTexCoord;

uniform mat4 cobblestoneModel;
uniform mat4 cobblestoneView;
uniform mat4 cobblestoneProjection;

void main()
{
	gl_Position = cobblestoneProjection * cobblestoneView * cobblestoneModel * vec4(aPos, 1.0f);
	cobblestoneTexCoord = vec2(aCobblestoneTexCoord.x, aCobblestoneTexCoord.y);
}