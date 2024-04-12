#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 testCubeModel;
uniform mat4 testCubeView;
uniform mat4 testCubeProjection;

void main()
{
    FragPos = vec3(testCubeModel * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(testCubeModel))) * aNormal;
	TexCoords = aTexCoords;
	gl_Position = testCubeProjection * testCubeView * vec4(FragPos, 1.0f);
}