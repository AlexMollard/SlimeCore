#version 450

out vec4 FragColour;

in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture1;

void main()
{
	FragColour = texture(texture1, texCoord);
}