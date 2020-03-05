#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec2 texCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform int lightIndex;

uniform vec3 diffuseColor;
void main()
{
	FragColour = vec4(diffuseColor, 1);
}