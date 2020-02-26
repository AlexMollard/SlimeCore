#include "ObjectManager.h"

ObjectManager::ObjectManager(MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* camPos)
{
	this->matManager = matManager;
	this->shaderManager = shaderManager;
	this->textureManager = textureManager;
	this->projectionView = projectionView;
	this->camPos = camPos;
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

void ObjectManager::Create(std::string name, Mesh* mesh, int materialIndex, int shaderIndex, glm::vec3 pos)
{
	objects.push_back(new GameObject(name, mesh, matManager->Get(materialIndex), shaderManager->Get(shaderIndex)));
	objects.back()->SetPos(pos);
}

void ObjectManager::Create(std::string name, Mesh* mesh, std::string materialName, std::string shaderName, glm::vec3 pos)
{
	objects.push_back(new GameObject(name, mesh, matManager->Get(materialName.c_str()), shaderManager->Get(shaderName.c_str())));
	objects.back()->SetPos(pos);
}

void ObjectManager::Swap(int objIndex, int vectorPos)
{
	GameObject* movingOBJ = objects[objIndex];
	GameObject* tempOBJ = objects[vectorPos];

	objects[vectorPos] = movingOBJ;
	objects[objIndex] = tempOBJ;
}

void ObjectManager::Add(GameObject* gameObject)
{
	objects.push_back(gameObject);
}

void ObjectManager::AddArray(GameObject** gameObject, int amount)
{
	for (int i = 0; i < amount; i++)
		objects.push_back(gameObject[i]);
}

void ObjectManager::AddArray(std::vector<GameObject*> gameObjects)
{
	AddArray(gameObjects.data(), gameObjects.size());
}

void ObjectManager::MoveObject(GameObject* obj, int newPos)
{
	int currentPos = FindIndex(obj);
}

int ObjectManager::FindIndex(GameObject* object)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] == object)
		{
			return i;
		}
	}

	printf("Object not found");
	return 404;
}

int ObjectManager::FindIndex(std::string name)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->name == name)
		{
			return i;
		}
	}

	printf("Object not found");
	return 404;
}

GameObject* ObjectManager::Get(int index)
{
	if (objects[index] == nullptr)
	{
		printf("Cannot find GameObject with index: %i", index);
		return nullptr;
	}

	return objects[index];
}

GameObject* ObjectManager::Get(std::string name)
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

std::vector<GameObject*> ObjectManager::GetVector(int start, int end)
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

bool ObjectManager::DebugManager()
{
	printf("GameObjects: \n");
	for (int i = 0; i < objects.size(); i++)
	{
		std::cout << " - " << objects[i]->name << std::endl;
	}
	printf("\n");

	return true;
}

bool ObjectManager::DebugAll()
{
	printf("\n");
	DebugManager();
	shaderManager->DebugManager();
	textureManager->DebugManager();
	matManager->DebugManager();
	return true;
}

bool ObjectManager::Draw()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (currentShader != objects[i]->shader)
		{
			objects[i]->shader->Use();
			currentShader = objects[i]->shader;
			objects[i]->UpdateUniforms(projectionView, *camPos);
		}

		if (objects[i]->GetTexture() != currentTexture)
		{
			currentTexture = objects[i]->GetTexture();
			glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture()->textureID);
		}

		if (objects[i]->name == "SkyBox")
		{
			glDepthMask(GL_FALSE);
			objects[i]->Draw(projectionView);
			glDepthMask(GL_TRUE);

			continue;
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
