#version 450

out vec4 FragColour;

in vec3 FragPos;
in vec3 normal;
in vec2 texCoord;

struct Material
{
	float shininess;
};

struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 albedo;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 albedo;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform vec3 viewPos;
uniform Material material;

uniform sampler2D diffuseTexture;
uniform int pointLightTotal;
#define MAX_LIGHTS 32
uniform PointLight pointLights[MAX_LIGHTS];
uniform DirectionalLight dirLight;

vec3 CalcDirectionLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(diffuseTexture, texCoord));
	vec3 albedo = light.albedo * diff * vec3(texture(diffuseTexture, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(diffuseTexture, texCoord));

	vec3 result = ambient + albedo + specular;// *texture(texture1, texCoord);
	return result;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 ambient = light.ambient * vec3(texture(diffuseTexture, texCoord));
	vec3 albedo = light.albedo * diff * vec3(texture(diffuseTexture, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(diffuseTexture, texCoord));

	ambient *= attenuation;
	albedo *= attenuation;
	specular *= attenuation;

	return (ambient + albedo + specular);
}

void main()
{
	vec3 norm = normalize(-normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	// Directional Light
	vec3 result = CalcDirectionLight(dirLight, norm, viewDir);

	// Point Lights
	for (int i = 0; i < pointLightTotal; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);

	FragColour = vec4(result, 1.0);
}