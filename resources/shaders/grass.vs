#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 grassModel;
uniform mat4 grassView;
uniform mat4 grassProjection;

void main()
{
    FragPos = vec3(grassModel * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(grassModel))) * aNormal;
	TexCoords = aTexCoords;
	gl_Position = grassProjection * grassView * vec4(FragPos, 1.0f);
}