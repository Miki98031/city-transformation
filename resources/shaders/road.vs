#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 roadModel;
uniform mat4 roadView;
uniform mat4 roadProjection;

void main()
{
    FragPos = vec3(roadModel * vec4(aPos, 1.0f));
	Normal = mat3(transpose(inverse(roadModel))) * aNormal;
	TexCoords = aTexCoords;
	gl_Position = roadProjection * roadView * vec4(FragPos, 1.0f);
}