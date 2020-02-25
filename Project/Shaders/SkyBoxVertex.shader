#version 450

layout(location = 0) in vec3 aPos;

out vec3 texCoord;

uniform mat4 ProjectionView;

void main()
{
    texCoord = aPos;
    vec4 pos = ProjectionView * vec4(aPos, 1.0);
    gl_Position = pos;
}