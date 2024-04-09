#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aBuildingRoofTexCoord;

out vec2 buildingRoofTexCoord;

uniform mat4 buildingRoofModel;
uniform mat4 buildingRoofView;
uniform mat4 buildingRoofProjection;

void main()
{
	gl_Position = buildingRoofProjection * buildingRoofView * buildingRoofModel * vec4(aPos, 1.0f);
	buildingRoofTexCoord = vec2(aBuildingRoofTexCoord.x, aBuildingRoofTexCoord.y);
}