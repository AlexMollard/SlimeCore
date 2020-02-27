#version 450

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 WorldPos;
out vec3 Normal;


uniform mat4 ProjectionView;
uniform mat4 Model; 

void main() 
{ 
    TexCoord = aTexCoord;
    WorldPos = vec3(Model * vec4(aPos, 1.0));
    Normal = mat3(Model) * aNormal;

    gl_Position = ProjectionView * vec4(WorldPos, 1.0);
}