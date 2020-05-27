#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(std::string name, glm::vec3 pos)
{
	SetName(name);
	SetPos(pos);
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SetDirectionalLightAttributes(glm::vec3 newDirection, glm::vec3 newAmbient, glm::vec3 newAlbedo, glm::vec3 newSpecular)
{
	SetDirectionalLightDirection(newDirection);
	SetDirectionalLightAmbient(newAmbient);
	SetDirectionalLightAlbedo(newAlbedo);
	SetDirectionalLightSpecular(newSpecular);
}