#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name, Mesh* mesh, Material* mat, Shader* shader, GameObject* parent)
{
	this->parent = parent;
	if (parent)
		parent->child.push_back(this);

	this->name = name;
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
	if (shader != nullptr)
	{
		shader->setMat4("ProjectionView", *ProjectionView);
		shader->setMat4("Model", model);
	}
	if (mesh != nullptr)
		mesh->draw(); 
}

void GameObject::UpdateUniforms(glm::mat4* ProjectionView, glm::vec3 cameraPos)
{
	// Material
	shader->setFloat("material.shininess", mat->GetShininess());
	shader->setVec3("viewPos", cameraPos);
}

void GameObject::SetPos(glm::vec3 newPos)
{
	position = newPos;
	model[3] = glm::vec4(newPos,1);
}


glm::vec3 GameObject::GetPos()
{
	return position;
}

void GameObject::AddRotate(float rotSpeed, glm::vec3 rotDIR)
{
	rotation = rotDIR;
	model = glm::rotate(model, rotSpeed, rotation);
}

void GameObject::SetRotate(glm::vec3 rotation)
{
	glm::vec3 updatedRotation = rotation * 3.141592f / 180.0f;
	glm::mat4 newModel = glm::mat4(1);
	newModel[3] = glm::vec4(position, 1);

	glm::mat4 mat = glm::mat4(1);
	newModel[0] = mat[0] * scale[0];
	newModel[1] = mat[1] * scale[1];
	newModel[2] = mat[2] * scale[2];
	newModel[3] = newModel[3];

	this->rotation = updatedRotation;

	glm::quat myQuat(updatedRotation);
	newModel *= glm::mat4(myQuat);

	model = newModel;
}

void GameObject::SetSkyBoxPos(glm::vec3* newPos)
{
	model[3][0] = newPos[0][0];
	model[3][1] = newPos[0][1];
	model[3][2] = newPos[0][2];
}

void GameObject::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	glm::mat4 mat = glm::mat4(1);
	model[0] = mat[0] * newScale[0];
	model[1] = mat[1] * newScale[1];
	model[2] = mat[2] * newScale[2];
	model[3] = model[3];

	//model = glm::scale(model, newScale);
}

glm::vec3 GameObject::GetScale()
{
	return scale;
}

bool GameObject::GetIsLight()
{
	return isPointLight;
}

void GameObject::SetIsLight(bool value)
{
	isPointLight = value;
}

void GameObject::SetMesh(Mesh* newMesh)
{
	mesh = newMesh;
}

void GameObject::SetMaterial(Material* newMaterial)
{
	mat = newMaterial;
}

Texture* GameObject::GetTexture(TEXTURETYPE type)
{
	switch (type)
	{
	case TEXTURETYPE::Albedo:
		return mat->GetAlbedo();
		break;
	case TEXTURETYPE::Specular:
		return mat->GetSpecMap();
		break;
	case TEXTURETYPE::Normal:
		return mat->GetNormalMap();
		break;
	case TEXTURETYPE::Ambient:
		return mat->GetAmbientMap();
		break;
	case TEXTURETYPE::SkyBox:
		printf("There is no skybox vector");
		break;
	case TEXTURETYPE::Rough:
		return mat->GetRoughMap();
		break;
	case TEXTURETYPE::Displacement:
		return mat->GetDisplacementMap();
		break;
	default:
		break;
	}
	return nullptr;
}

Shader* GameObject::GetShader()
{
	return shader;
}

void GameObject::SetShader(Shader* newShader)
{
	shader = newShader;
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::SetName(std::string newName)
{
	name = newName;
}

std::string GameObject::GetDescription()
{
	return description;
}

void GameObject::SetDescription(std::string newDesc)
{
	description = newDesc;
}

GameObject* GameObject::GetChild(int index)
{
	if (child.size() < 1)
	{
		std::cout << name << " Has no children" << std::endl;
		return nullptr;
	}

	if (child[index] != nullptr)
		return child[index];

	std::cout << "Tried to grab a child from " << name << " that doesent exist." << std::endl;
	return nullptr;
}

GameObject* GameObject::GetChild(std::string name)
{
	if (child.size() < 1)
	{
		std::cout << name << " Has no children" << std::endl;
		return nullptr;
	}

	for (int i = 0; i < child.size(); i++)
		if (child[i]->name == name)
			return child[i];

	std::cout << "Tried to grab a child from " << name << " that doesent exist." << std::endl;
	return nullptr;
}

std::vector<GameObject*> GameObject::GetChildren()
{
	if (child.size() < 1)
	{
		std::cout << name << "Has no children" << std::endl;
		return std::vector<GameObject*>();
	}

	return child;
}

int GameObject::GetChildCount()
{
	return child.size();
}

void GameObject::AddChild(GameObject* newChild)
{
	child.push_back(newChild);
}

void GameObject::RemoveChild(GameObject* oldChild)
{
	int oldChildIndex = FindChild(oldChild);
	std::vector<GameObject*> newChildrenVector;
	for (int i = 0; i < child.size(); i++)
	{
		if (i == oldChildIndex)
			continue;

		newChildrenVector.push_back(child[i]);
	}

	child.clear();
	child = newChildrenVector;
}

int GameObject::FindChild(GameObject* childToFind)
{
	for (int i = 0; i < child.size(); i++)
	{
		if (child[i] == childToFind)
			return i;
	}
	std::cout << "Cant find child!" << std::endl;
	return -404;
}

void GameObject::SetParent(GameObject* newParent)
{
	if (parent != nullptr)
	{
		std::cout << "OverWritten the parent for object " << name << "." << std::endl;
	}

	if (newParent != nullptr)
		newParent->AddChild(this);

	parent = newParent;
}

GameObject* GameObject::GetParent()
{
	if (parent != nullptr)
		return parent;

	return nullptr;
}
