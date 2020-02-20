#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Material* mat, Shader* shader)
{
	this->mesh = mesh;
	this->mat = mat;
	this->shader = shader;
}

GameObject::~GameObject()
{
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
	shader->setMat4("ProjectionView", *ProjectionView);
	shader->setMat4("Model", model);
	mesh->draw(); 
}

void GameObject::UpdateUniforms(glm::mat4* ProjectionView)
{
	// Material
	shader->setVec3("material.ambient", mat->ambient);
	shader->setVec3("material.diffuseColor", mat->diffuseColor);
	shader->setVec3("material.specular", mat->specular);
	shader->setFloat("material.shininess", mat->shininess);

	// Spot Lights
	for (int i = 0; i < 4; i++)
	{
		shader->setVec3("pointLights[" + std::to_string(i) + "].position", mat->pointLights[i].lightPosition);
		shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", mat->pointLights[i].lightAmbient);
		shader->setVec3("pointLights[" + std::to_string(i) + "].diffuse", mat->pointLights[i].lightDiffuse);
		shader->setVec3("pointLights[" + std::to_string(i) + "].specular", mat->pointLights[i].lightSpecular);
		
		shader->setFloat("pointLights[" + std::to_string(i) + "].constant", mat->pointLights[i].lightConstant);
		shader->setFloat("pointLights[" + std::to_string(i) + "].linear", mat->pointLights[i].lightLinear);
		shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", mat->pointLights[i].lightQuadratic);
	}

	// Directional Light
	shader->setVec3("dirLight.direction", mat->dirLightDirection);
	shader->setVec3("dirLight.ambient", mat->dirLightAmbient);
	shader->setVec3("dirLight.diffuse", mat->dirLightDiffuse);
	shader->setVec3("dirLight.specular", mat->dirLightSpecular);
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