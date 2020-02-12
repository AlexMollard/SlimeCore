#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 lightColor = vec3(1.0,0.75,0.5);

	// ambiant
	float ambiantStrength = 0.4;
	vec3 ambient = ambiantStrength * lightColor;
	
	// diffuse
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec4 result = vec4(ambient + diffuse + specular,1.0) * texture(texture1, texCoord);
	FragColour = result;
}