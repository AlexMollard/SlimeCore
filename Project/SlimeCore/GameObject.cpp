#include "GameObject.h"

GameObject::GameObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, Mesh* mesh, Material* material)
{
	position = pos;
	
	if (mesh != nullptr)
		this->mesh = mesh;
	else
	{
		this->mesh = new Mesh();
		this->mesh->InitialiseQuad();
	}

	if (material != nullptr)
		this->mat = material;
	else
		mat = new Material();

	model[3] = glm::vec4(position, 1);
	model = glm::scale(model, scale);
	model = glm::rotate(model, 1.0f, rotation);
}

GameObject::~GameObject()
{
	if(mat)
	delete mat;
	if(mesh)
	delete mesh;
}

glm::mat4 GameObject::GetModel()
{
	return model;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(glm::mat4* ProjectionView)
{
	mat->GetShader()->Use();
	mat->GetShader()->setMat4("ProjectionView", *ProjectionView);
	mat->GetShader()->setMat4("Model", model);

	mesh->Draw(); 
}

void GameObject::SetPos(glm::vec3 newPos)
{
	position = newPos;
	model[3] = glm::vec4(newPos,1);
}

void GameObject::AddRotate(float rotSpeed, glm::vec3 rotDIR)
{
	rotation = rotDIR;
	model = glm::rotate(model, rotSpeed, rotation);
}
