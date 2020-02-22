#include "ObjectManager.h"

ObjectManager::ObjectManager(MaterialManager* matManager, ShaderManager* shaderManager, glm::mat4* projectionView)
{
	this->matManager = matManager;
	this->shaderManager = shaderManager;
	this->projectionView = projectionView;
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i])
		{
			delete objects[i];
			objects[i] = nullptr;
		}
	}
}

void ObjectManager::CreateGameObject(std::string name, Mesh* mesh, int materialIndex, int shaderIndex, glm::vec3 pos)
{
	objects.push_back(new GameObject(name, mesh, matManager->GetMaterialByIndex(materialIndex), shaderManager->GetShaderByIndex(shaderIndex)));
	objects.back()->SetPos(pos);
}

void ObjectManager::CreateGameObject(std::string name, Mesh* mesh, std::string materialName, std::string shaderName, glm::vec3 pos)
{
	objects.push_back(new GameObject(name, mesh, matManager->GetMaterialByName(true, materialName.c_str()), shaderManager->GetShaderByName(true, shaderName.c_str())));
	objects.back()->SetPos(pos);
}

void ObjectManager::AddGameObject(GameObject* gameObject)
{
	objects.push_back(gameObject);
}

void ObjectManager::AddGameObjectArray(GameObject** gameObject, int amount)
{
	for (int i = 0; i < amount; i++)
		objects.push_back(gameObject[i]);
}

void ObjectManager::AddGameObjectArray(std::vector<GameObject*> gameObjects)
{
	AddGameObjectArray(gameObjects.data(), gameObjects.size());
}

GameObject* ObjectManager::GetGameObject(int index)
{
	if (objects[index] == nullptr)
	{
		printf("Cannot find GameObject with index: %i", index);
		return nullptr;
	}

	return objects[index];
}

GameObject* ObjectManager::GetGameObject(std::string name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->name == name)
		{
			return objects[i];
		}
	}

	printf("Cannot find GameObject with name: %s", name.c_str());
	return nullptr;
}

std::vector<GameObject*> ObjectManager::GetGameObjectVector(int start, int end)
{
	if (start < 0 || end > objects.size())
	{
		printf("OUT OF SCOPE: Get Game Array. \n");
		return std::vector<GameObject*>();
	}

	std::vector<GameObject*> gameObjects;

	for (int i = start; i < end; i++)
	{
		gameObjects.push_back(objects[i]);
	}

	return gameObjects;
}

void ObjectManager::SetNamesVector()
{
	names.clear();
	for (int i = 0; i < objects.size(); i++)
	{
		names.push_back(objects[i]->name.c_str());
	}
}

std::vector<const char*> ObjectManager::GetNameVector()
{
	return names;
}

bool ObjectManager::Draw()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (currentShader != objects[i]->shader)
		{
			objects[i]->shader->Use();
			currentShader = objects[i]->shader;
			objects[i]->UpdateUniforms(projectionView);
		}

		if (objects[i]->GetTexture() != currentTexture)
		{
			currentTexture = objects[i]->GetTexture();
			glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture()->textureID);
		}

		objects[i]->Draw(projectionView);
	}
	return true;
}

bool ObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(deltaTime);
	}
	return true;
}
