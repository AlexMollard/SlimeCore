#version 450

layout(location = 0) in vec3 aPos;

uniform mat4 ProjectionView;
uniform mat4 Model; 

void main() 
{ 
	gl_Position = ProjectionView * Model * vec4(aPos, 1.0);
}