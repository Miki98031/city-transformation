#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aRoadTexCoord;

out vec2 roadTexCoord;

uniform mat4 roadModel;
uniform mat4 roadView;
uniform mat4 roadProjection;

void main()
{
	gl_Position = roadProjection * roadView * roadModel * vec4(aPos, 1.0f);
	roadTexCoord = vec2(aRoadTexCoord.x, aRoadTexCoord.y);
}