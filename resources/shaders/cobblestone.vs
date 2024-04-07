#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aCobblestoneTexCoord;
layout (location = 2) in float aRotateAngle;

out vec2 cobblestoneTexCoord;

uniform mat4 cobblestoneModel;
uniform mat4 cobblestoneView;
uniform mat4 cobblestoneProjection;

void main()
{
    mat2 rotMat;
    rotMat[0][0] = cos(radians(aRotateAngle));
    rotMat[0][1] = sin(radians(aRotateAngle));
    rotMat[1][0] = -sin(radians(aRotateAngle));
    rotMat[1][1] = cos(radians(aRotateAngle));

	gl_Position = cobblestoneProjection * cobblestoneView * cobblestoneModel * vec4(aPos, 1.0f);
	cobblestoneTexCoord = vec2(aCobblestoneTexCoord.x, aCobblestoneTexCoord.y);
}