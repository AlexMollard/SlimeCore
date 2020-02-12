#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 lightPos;

void main()
{
	vec3 lightColor = vec3(1.0,1.0,0.0);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float ambiantStrength = 0.4;
	vec3 ambient = ambiantStrength * lightColor;

	vec4 result = vec4(ambient + diffuse,1.0) * texture(texture1, texCoord);
	FragColour = result;
}