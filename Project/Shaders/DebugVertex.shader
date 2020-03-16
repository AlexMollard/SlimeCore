#version 450

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords;
    vec3 Pos = aPos;
    gl_Position = vec4(Pos.xy, 0.0, 1.0);
}