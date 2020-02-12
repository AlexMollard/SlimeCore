#include "GameObject.h"

GameObject::GameObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, Mesh* mesh, Material* material)
{
	position = pos;
	
	if (mesh != nullptr)
		this->mesh = mesh;
	else
	{
		this->mesh = new Mesh();
		this->mesh->create();
	}

	if (material != nullptr)
		this->mat = material;
	else
		mat = new Material();

	model[3] = glm::vec4(position, 1);
	model = glm::scale(model, scale);

	// Need to fix
	//model = glm::rotate(model, 0.0f, rotation);
}

GameObject::GameObject(glm::vec3 pos, Primitives::TYPE type, Texture* texture, float argOne, float argTwo, int argThree)
{
	position = pos;

	this->mesh = new Mesh();
	this->mesh->create(type, argOne, argTwo, argThree);

	mat = new Material(nullptr, texture);

	model[3] = glm::vec4(position, 1);
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

void GameObject::Draw(glm::mat4* ProjectionView, Camera* cam, glm::vec3 lightPos)
{
	mat->GetShader()->Use();
	mat->GetShader()->setMat4("ProjectionView", *ProjectionView);
	mat->GetShader()->setMat4("Model", model);
	mat->GetShader()->setVec3("lightPos", lightPos);
	mat->GetShader()->setVec3("viewPos", cam->Position);
	glBindTexture(GL_TEXTURE_2D, mat->GetTexture()->textureID);

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

void GameObject::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	model = glm::scale(model, newScale);
}