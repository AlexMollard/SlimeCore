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

	SetDirectionalLightAttributes();
}

Material::~Material()
{
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

void Material::SetDiffuse(Texture* newDiffuse)
{
	diffuse = newDiffuse;
}

void Material::SetSpecMap(Texture* newSpecular)
{
	specMap = newSpecular;
}

void Material::SetNormalMap(Texture* newNormal)
{
	normalMap = newNormal;
}

void Material::SetAmbientMap(Texture* newAmbient)
{
	ambientMap = newAmbient;
}

void Material::SetRoughMap(Texture* newRough)
{
	roughMap = newRough;
}