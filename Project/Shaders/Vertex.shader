#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 ProjectionView;
uniform mat4 Model; 

out vec3 FragPos;
out vec3 normal;
out vec2 texCoord;

void main() 
{ 
	gl_Position = ProjectionView * Model * vec4(aPos, 1.0);
	normal = aNormal;
	FragPos = vec3(Model * vec4(aPos, 1.0));
	texCoord = vec2(aTexCoord.x, aTexCoord.y);
}