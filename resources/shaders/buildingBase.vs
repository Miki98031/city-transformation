#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 buildingBaseModel;
uniform mat4 buildingBaseView;
uniform mat4 buildingBaseProjection;

void main()
{
	gl_Position = buildingBaseProjection * buildingBaseView * buildingBaseModel * vec4(aPos, 1.0f);
}