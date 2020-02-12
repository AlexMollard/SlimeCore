#include "Material.h"

Material::Material(Shader* shader, Texture* texture)
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
}

Material::~Material()
{
	if (shader)
		delete shader;

	if (texture && hasOwnTexture == false)
		delete texture;
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
