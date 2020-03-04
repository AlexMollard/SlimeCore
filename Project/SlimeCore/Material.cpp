#include "Material.h"

Material::Material(std::string name, Texture* diffuse, Texture* specMap, Texture* normalMap, Texture* ambientMap, Texture* roughMap)
{
	this->name = name;

	this->diffuse = diffuse;
	
	if (specMap)
		hasSpecMap = true;
	this->specMap = specMap;
	
	if (normalMap)
		hasNormalMap = true;
	this->normalMap = normalMap;

	if (ambientMap)
		hasSpecColorMap = true;
	this->ambientMap = ambientMap;

	if (ambientMap)
		hasRoughMap = true;
	this->roughMap = roughMap;

	setMatAtrributes();
	pointLights->SetLightAttributes();
	SetDirectionalLightAttributes();
}

Material::Material(std::string name, Texture* diffuse, float diffuseStrength, Texture* specMap, float specularStrength, Texture* normalMap, float normalStrength, Texture* ambientMap, float ambientStrength, Texture* roughMap, float roughStrength)
{
	this->name = name;

	this->diffuse = diffuse;

	if (specMap)
		hasSpecMap = true;
	this->specMap = specMap;

	if (normalMap)
		hasNormalMap = true;
	this->normalMap = normalMap;

	if (ambientMap)
		hasSpecColorMap = true;
	this->ambientMap = ambientMap;

	if (ambientMap)
		hasRoughMap = true;
	this->roughMap = roughMap;

	this->diffuseStrength = diffuseStrength;
	this->specularStrength = specularStrength;
	this->normalStrength = normalStrength;
	this->ambientStrength = ambientStrength;
	this->roughStrength = roughStrength;

	setMatAtrributes();
	pointLights->SetLightAttributes();
	SetDirectionalLightAttributes();
}

Material::Material(std::string name, Texture* diffuse)
{
	this->name = name;

	this->diffuse = diffuse;
	this->specMap = nullptr;
	this->normalMap = nullptr;
	this->ambientMap = nullptr;
	this->roughMap = nullptr;

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

Texture* Material::GetAmbientMap()
{
	if (ambientMap != nullptr)
		return ambientMap;

	return nullptr;
}

Texture* Material::GetRoughMap()
{
	if (roughMap != nullptr)
		return roughMap;

	return nullptr;
}

