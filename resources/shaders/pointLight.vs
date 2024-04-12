#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 pointLightModel;
uniform mat4 pointLightView;
uniform mat4 pointLightProjection;

void main()
{
	gl_Position = pointLightProjection * pointLightView * pointLightModel * vec4(aPos, 1.0);
}