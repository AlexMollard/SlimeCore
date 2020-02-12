#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	FragColour = texture(texture1, texCoord);
}