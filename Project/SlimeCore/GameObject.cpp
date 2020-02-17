#include "GameObject.h"

GameObject::GameObject(Mesh* mesh, Material* mat, Shader* shader, Texture* texture)
{
	if (mesh)
	{
		this->mesh = mesh;
		userMesh = true;
	}
	else
	{
		this->mesh = new Mesh();
		this->mesh->create(Primitives::TYPE::Cube);
	}

	if (mat)
	{
		this->mat = mat;
		userMat = true;
	}
	else
		this->mat = new Material(shader ?  shader : nullptr, texture ? texture : nullptr);
}

GameObject::GameObject(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, Mesh* mesh, Material* material)
{
	position = pos;
	
	if (mesh != nullptr) 
	{
		this->mesh = mesh;
		userMesh = true;
	}
	else
	{
		this->mesh = new Mesh();
		this->mesh->create();
	}

	if (material != nullptr)
	{
		this->mat = material;
		userMat = true;
	}
	else
		mat = new Material();

	model[3] = glm::vec4(position, 1);
	model = glm::scale(model, scale);

	// Need to fix
	model = glm::rotate(model, 2.1f, rotation);
}

GameObject::GameObject(glm::vec3 pos, Primitives::TYPE type, Texture* texture, float argOne, float argTwo, int argThree)
{
	position = pos;

	this->mesh = new Mesh();
	this->mesh->create(type, argOne, argTwo, argThree);
	userMesh = false;

	mat = new Material(nullptr, texture);
	userMat = false;

	model[3] = glm::vec4(position, 1);
}

GameObject::~GameObject()
{
	if(mat && !userMat)
	delete mat;
	if(mesh && !userMesh)
	delete mesh;
}

glm::mat4 GameObject::GetModel()
{
	return model;
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::Draw(glm::mat4* ProjectionView, Camera* cam)
{
	if (ProjectionView != nullptr && cam != nullptr)
		UpdateUniforms(ProjectionView, cam);

	glBindTexture(GL_TEXTURE_2D, mat->GetTexture()->textureID);
	mesh->draw(); 
}

void GameObject::UpdateUniforms(glm::mat4* ProjectionView, Camera* cam)
{
	mat->GetShader()->Use();
	mat->GetShader()->setMat4("ProjectionView", *ProjectionView);
	mat->GetShader()->setVec3("viewPos", cam->Position);
	mat->GetShader()->setMat4("Model", model);

	// Material
	mat->GetShader()->setVec3("material.ambient", mat->ambient);
	mat->GetShader()->setVec3("material.diffuseColor", mat->diffuseColor);
	mat->GetShader()->setVec3("material.specular", mat->specular);
	mat->GetShader()->setFloat("material.shininess", mat->shininess);

	// Spot Lights
	for (int i = 0; i < 4; i++)
	{
		mat->GetShader()->setVec3("pointLights[" + std::to_string(i) + "].position", mat->pointLights[i].lightPosition);
		mat->GetShader()->setVec3("pointLights[" + std::to_string(i) + "].ambient", mat->pointLights[i].lightAmbient);
		mat->GetShader()->setVec3("pointLights[" + std::to_string(i) + "].diffuse", mat->pointLights[i].lightDiffuse);
		mat->GetShader()->setVec3("pointLights[" + std::to_string(i) + "].specular", mat->pointLights[i].lightSpecular);

		mat->GetShader()->setFloat("pointLights[" + std::to_string(i) + "].constant", mat->pointLights[i].lightConstant);
		mat->GetShader()->setFloat("pointLights[" + std::to_string(i) + "].linear", mat->pointLights[i].lightLinear);
		mat->GetShader()->setFloat("pointLights[" + std::to_string(i) + "].quadratic", mat->pointLights[i].lightQuadratic);
	}

	// Directional Light
	mat->GetShader()->setVec3("dirLight.direction", mat->dirLightDirection);
	mat->GetShader()->setVec3("dirLight.ambient", mat->dirLightAmbient);
	mat->GetShader()->setVec3("dirLight.diffuse", mat->dirLightDiffuse);
	mat->GetShader()->setVec3("dirLight.specular", mat->dirLightSpecular);
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