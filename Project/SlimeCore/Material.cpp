#include "Material.h"

Material::Material(Shader* shader, Texture* texture, glm::vec3 newAmbient, glm::vec3 newDiffuseColor, glm::vec3 newSpecular, float newShininess)
{
	if (shader == nullptr)
		this->shader = new Shader("..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	else
		this->shader = shader;

	if (texture == nullptr)
		this->texture = new Texture("..\\Images\\missingTex.png");
	else
	{
		hasOwnTexture = true;
		this->texture = texture;
	}

	setAmbient(newAmbient);
	setDiffuseColor(newDiffuseColor);
	setSpecular(newSpecular);
	setShininess(newShininess);
}

Material::~Material()
{
	if (shader)
		delete shader;

	if (texture && hasOwnTexture == false)
		delete texture;
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

Shader* Material::GetShader()
{
	if (shader != nullptr)
		return shader;

	return nullptr;
}

Texture* Material::GetTexture()
{
	if (shader != nullptr)
		return texture;

	return nullptr;
}

