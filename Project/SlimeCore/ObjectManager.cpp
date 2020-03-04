#include "ObjectManager.h"

ObjectManager::ObjectManager(MeshManager* meshManager, MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* camPos)
{
	this->matManager = matManager;
	this->shaderManager = shaderManager;
	this->textureManager = textureManager;
	this->meshManager = meshManager;
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

GameObject* ObjectManager::Create(std::string name, int meshIndex, int materialIndex, int shaderIndex, int parent, glm::vec3 pos)
{
	if (parent > 0)
		objects.push_back(new GameObject(name, meshManager->Get(meshIndex), matManager->Get(materialIndex), shaderManager->Get(shaderIndex), Get(parent)));
	else
		objects.push_back(new GameObject(name, meshManager->Get(meshIndex), matManager->Get(materialIndex), shaderManager->Get(shaderIndex)));

	objects.back()->SetPos(pos);
	return objects.back();
}

GameObject* ObjectManager::Create(std::string name, std::string  meshName, std::string materialName, std::string shaderName, std::string parent, glm::vec3 pos)
{
	if (parent.size() > 0)
		objects.push_back(new GameObject(name, meshManager->Get(meshName.c_str()), matManager->Get(materialName.c_str()), shaderManager->Get(shaderName.c_str()), Get(parent)));
	else
		objects.push_back(new GameObject(name, meshManager->Get(meshName.c_str()), matManager->Get(materialName.c_str()), shaderManager->Get(shaderName.c_str())));

	objects.back()->SetPos(pos);
	return objects.back();
}

void ObjectManager::Create(GameObject* parent)
{
	GameObject* go = new GameObject("New GameObject", nullptr, nullptr, nullptr, parent);
	Add(go);
	std::cout << "IMGUI just made a object" << std::endl;
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
		if (objects[i]->GetName() == name)
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
		if (objects[i]->GetName() == name)
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

void ObjectManager::SetVars(int index, std::string name, bool isStatic, glm::vec3 pos, glm::vec4 rotation, glm::vec3 scale, std::string meshName, std::string materialName, std::string shaderName)
{
	GameObject* go = Get(index);
	go->SetName(name);
	go->SetPos(pos);
	go->SetScale(scale);
	go->SetMesh(meshManager->Get(meshName.c_str()));
	go->SetMaterial(matManager->Get(materialName.c_str()));
	go->SetShader(shaderManager->Get(shaderName.c_str()));
}

void ObjectManager::SetNamesVector()
{
	names.clear();
	for (int i = 0; i < objects.size(); i++)
	{
		names.push_back(objects[i]->GetName().c_str());
	}
	textureManager->SetNameList();
}

std::vector<std::string> ObjectManager::GetNameVector()
{
	SetNamesVector();
	return names;
}

bool ObjectManager::DebugManager()
{
	printf("GameObjects: \n");
	for (int i = 0; i < objects.size(); i++)
	{
		std::cout << " - " << objects[i]->GetName() << std::endl;
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
	matManager->SetDirLightDirection(glm::vec3(0, -1, -0.3));
	
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetShader()->name != "None")
		{
			if (currentShader != objects[i]->GetShader())
			{
				objects[i]->GetShader()->Use();
				currentShader = objects[i]->GetShader();
				objects[i]->UpdateUniforms(projectionView, *camPos);
			}
		}

		if (objects[i]->GetMaterial()->name != "None")
		{
			if (currentMaterial != objects[i]->GetMaterial())
			{
				currentMaterial = objects[i]->GetMaterial();
				currentDiffuse = nullptr;
				currentSpecular = nullptr;
				currentNormal = nullptr;
				currentAmbient = nullptr;
			}

			if (objects[i]->GetTexture(TEXTURETYPE::Diffuse)->name != "None")
			{
				if (objects[i]->GetTexture(TEXTURETYPE::Diffuse) != currentDiffuse)
				{
					objects[i]->GetShader()->setInt("diffuseTexture", 0);
					currentDiffuse = objects[i]->GetTexture(TEXTURETYPE::Diffuse);
					glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
					glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Diffuse)->textureID);
					objects[i]->GetShader()->setFloat("diffuseStrength", objects[i]->GetMaterial()->diffuseStrength);
				}
			}

			if (objects[i]->GetName() == "SkyBox")
			{
				glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
				glDepthMask(GL_FALSE);
				objects[i]->Draw(projectionView);
				glDepthMask(GL_TRUE);

				continue;
			}

			if (objects[i]->GetTexture(TEXTURETYPE::Specular) != nullptr)
			{
				if (objects[i]->GetTexture(TEXTURETYPE::Specular)->name != "None")
				{
					if (objects[i]->GetTexture(TEXTURETYPE::Specular) != currentSpecular)
					{
						objects[i]->GetShader()->setInt("specularTexture", 1);
						currentSpecular = objects[i]->GetTexture(TEXTURETYPE::Specular);
						glActiveTexture(GL_TEXTURE0 + 1); // Texture unit 1
						glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Specular)->textureID);
						objects[i]->GetShader()->setFloat("specularStrength", objects[i]->GetMaterial()->specularStrength);
					}
				}
			}

			if (objects[i]->GetTexture(TEXTURETYPE::Normal) != nullptr)
			{
				if (objects[i]->GetTexture(TEXTURETYPE::Normal)->name != "None")
				{
					if (objects[i]->GetTexture(TEXTURETYPE::Normal) != currentNormal)
					{
						objects[i]->GetShader()->setInt("normalTexture", 2);
						currentNormal = objects[i]->GetTexture(TEXTURETYPE::Normal);
						glActiveTexture(GL_TEXTURE0 + 2); // Texture unit 2
						glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Normal)->textureID);
						objects[i]->GetShader()->setFloat("normalStrength", objects[i]->GetMaterial()->normalStrength);
					}
				}
			}

			if (objects[i]->GetTexture(TEXTURETYPE::Ambient) != nullptr)
			{
				if (objects[i]->GetTexture(TEXTURETYPE::Ambient)->name != "None")
				{
					if (objects[i]->GetTexture(TEXTURETYPE::Ambient) != currentAmbient)
					{
						objects[i]->GetShader()->setInt("ambientTexture", 3);
						currentAmbient = objects[i]->GetTexture(TEXTURETYPE::Ambient);
						glActiveTexture(GL_TEXTURE0 + 3); // Texture unit 3
						glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Ambient)->textureID);
						objects[i]->GetShader()->setFloat("ambientStrength", objects[i]->GetMaterial()->ambientStrength);
					}
				}
			}

			if (objects[i]->GetTexture(TEXTURETYPE::Rough) != nullptr)
			{
				if (objects[i]->GetTexture(TEXTURETYPE::Rough)->name != "None")
				{
					if (objects[i]->GetTexture(TEXTURETYPE::Rough) != currentRough)
					{
						objects[i]->GetShader()->setInt("roughTexture", 3);
						currentRough = objects[i]->GetTexture(TEXTURETYPE::Rough);
						glActiveTexture(GL_TEXTURE0 + 3); // Texture unit 3
						glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Rough)->textureID);
						objects[i]->GetShader()->setFloat("roughStrength", objects[i]->GetMaterial()->roughStrength);
					}
				}
			}
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
