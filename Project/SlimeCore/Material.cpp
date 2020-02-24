#include "Material.h"

Material::Material(const char* name, Texture* texture)
{
	this->name = name;

	this->texture = texture;

	setMatAtrributes();
	pointLights->SetLightAttributes();
	SetDirectionalLightAttributes();
}

Material::~Material()
{
}

void Material::setMatAtrributes(glm::vec3 newAmbient, glm::vec3 newDiffuseColor, glm::vec3 newSpecular, float newShininess)
{
	setAmbient(newAmbient);
	setDiffuseColor(newDiffuseColor);
	setSpecular(newSpecular);
	setShininess(newShininess);
}

void Material::PointLight::SetLightAttributes(glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular, float newConstant, float newLinear, float newQuadratic)
{
	SetLightAmbient(newAmbient);
	SetLightDiffuse(newDiffuse);
	SetLightSpecular(newSpecular);

	SetLightConstant(newConstant);
	SetLightLinear(newLinear);
	SetLightQuadratic(newQuadratic);
}

void Material::SetDirectionalLightAttributes(glm::vec3 newDirection, glm::vec3 newAmbient, glm::vec3 newDiffuse, glm::vec3 newSpecular)
{
	SetDirectionalLightDirection(newDirection);
	SetDirectionalLightAmbient(newAmbient);
	SetDirectionalLightDiffuse(newDiffuse);
	SetDirectionalLightSpecular(newSpecular);
}

Texture* Material::GetTexture()
{
	if (texture != nullptr)
		return texture;

	return nullptr;
}

