#include "Material.h"

Material::Material(Shader* shader)
{
	if (shader == nullptr)
		this->shader = new Shader("..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	else
		this->shader = shader;

}

Material::~Material()
{
	if (shader)
		delete shader;
}

Shader* Material::GetShader()
{
	if (shader != nullptr)
		return shader;
}
