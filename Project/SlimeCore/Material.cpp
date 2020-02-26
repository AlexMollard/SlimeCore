#include "Material.h"

Material::Material(const char* name, Texture* diffuse, Texture* specMap, Texture* normalMap, Texture* specColorMap)
{
	this->name = name;

	this->diffuse = diffuse;
	
	if (specMap)
		hasSpecMap = true;
	this->specMap = specMap;
	
	if (normalMap)
		hasNormalMap = true;
	this->normalMap = normalMap;

	if (specColorMap)
		hasSpecColorMap = true;
	this->specColorMap = specColorMap;

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

Texture* Material::GetDiffuse()
{
	if (diffuse != nullptr)
		return diffuse;

	return nullptr;
}

Texture* Material::GetSpecMap()
{
	if (specMap != nullptr)
		return specMap;

	return nullptr;
}

Texture* Material::GetNormalMap()
{
	if (normalMap != nullptr)
		return normalMap;

	return nullptr;
}

Texture* Material::GetSpecColorMap()
{
	if (specColorMap != nullptr)
		return specColorMap;

	return nullptr;
}

