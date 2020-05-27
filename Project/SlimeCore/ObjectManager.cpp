#include "ObjectManager.h"

ObjectManager::ObjectManager(MeshManager* meshManager, MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* camPos)
{
	this->matManager = matManager;
	this->shaderManager = shaderManager;
	this->textureManager = textureManager;
	this->meshManager = meshManager;
	this->projectionView = projectionView;
	this->camPos = camPos;

	CreateDirectionalLight();
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

	delete matManager;
	delete shaderManager;
	delete textureManager;
	delete meshManager;
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

GameObject* ObjectManager::Create(std::string name, Primitives::TYPE type, int materialIndex, int shaderIndex, int parent, glm::vec3 pos)
{
	int objectType = 0;
	switch (type)
	{
	case Primitives::Cube:
		objectType = 2;
		break;
	default:
		break;
	}

	return Create("Block", objectType, 2, 3);
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

GameObject* ObjectManager::Create(GameObject* parent, std::string name)
{
	GameObject* go = new GameObject(name, nullptr, nullptr, nullptr, parent);
	go->SetPos(glm::vec3(0));
	Add(go);
	std::cout << "IMGUI just made a object" << std::endl;
	return go;
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

void ObjectManager::Add(GameObject** gameObject, int amount)
{
	for (int i = 0; i < amount; i++)
		objects.push_back(gameObject[i]);
}

void ObjectManager::Add(std::vector<GameObject*> gameObjects)
{
	Add(gameObjects.data(), gameObjects.size());
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
	return -404;
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
	return -404;
}

int ObjectManager::GetObjectSize()
{
	return objects.size();
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

std::vector<GameObject*> ObjectManager::Get(int start, int end)
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

void ObjectManager::SetVars(int index, std::string name, bool isStatic, glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::string meshName, std::string materialName, std::string shaderName)
{
	GameObject* go = Get(index);
	go->SetName(name);
	go->SetPos(pos);
	go->SetScale(scale);

	go->SetRotate(rotation);
	if (meshName != "")
		go->SetMesh(meshManager->Get(meshName.c_str()));

	if (materialName != "")
		go->SetMaterial(matManager->Get(materialName));

	if (shaderName != "")
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

int ObjectManager::FindPointLight(GameObject* lightObject)
{
	for (int i = 0; i < pointLights.size(); i++)
	{
		if (pointLights[i] == lightObject)
			return i;
	}

	std::cout << "Cannot find a light." << std::endl;
	return -404;
}

PointLight* ObjectManager::CreatePointLight(std::string name, glm::vec3 pos, GameObject* parent)
{
	PointLight* pLight = new PointLight(name, pos);
	pLight->SetShader(shaderManager->Get("lightShader"));
	pLight->SetMaterial(matManager->Get("None"));
	pLight->SetMesh(meshManager->Get("Cube"));
	pLight->SetScale(glm::vec3(0.1f));
	pLight->SetIsLight(true);

	if (parent != nullptr)
		pLight->SetParent(parent);

	AddPointLight(pLight);
	return pLight;
}

void ObjectManager::AddPointLight(PointLight* light)
{
	pointLights.push_back(light);
	Add(light);
}

void ObjectManager::CreateDirectionalLight()
{
	DirectionalLight* pLight = new DirectionalLight("DirectionalLight", glm::vec3(0));
	pLight->SetShader(shaderManager->Get("None"));
	pLight->SetMaterial(matManager->Get("None"));
	pLight->SetMesh(meshManager->Get("None"));
	pLight->SetIsLight(true);
	directionalLight = pLight;
	Add(pLight);
}

void ObjectManager::UpdateLights(Shader* shader)
{
	// Spot Lights

	shader->setInt("pointLightTotal", pointLights.size());
	for (int i = 0; i < pointLights.size(); i++)
	{
		shader->setVec3("pointLights[" + std::to_string(i) + "].position", pointLights[i]->GetPos());
		shader->setVec3("pointLights[" + std::to_string(i) + "].ambient", pointLights[i]->GetAmbient());
		shader->setVec3("pointLights[" + std::to_string(i) + "].albedo", pointLights[i]->GetAlbedo());
		shader->setVec3("pointLights[" + std::to_string(i) + "].specular", pointLights[i]->GetSpecular());

		shader->setFloat("pointLights[" + std::to_string(i) + "].strength", pointLights[i]->GetStrength());

		shader->setFloat("pointLights[" + std::to_string(i) + "].constant", pointLights[i]->GetConstant());
		shader->setFloat("pointLights[" + std::to_string(i) + "].linear", pointLights[i]->GetLinear());
		shader->setFloat("pointLights[" + std::to_string(i) + "].quadratic", pointLights[i]->GetQuadratic());
	}

	shader->setVec3("dirLight.direction", directionalLight->GetRotation());
	shader->setVec3("dirLight.ambient", directionalLight->dirLightAmbient);
	shader->setVec3("dirLight.albedo", directionalLight->dirLightAlbedo);
	shader->setVec3("dirLight.specular", directionalLight->dirLightSpecular);
}

void ObjectManager::BindTexture(int objectIndex, TEXTURETYPE texType, Texture* texture)
{
	if (texture != nullptr)
	{
		if (texture != currentTexture[(int)texType])
		{
			SetIntTexture(objectIndex, texType);
			currentTexture[(int)texType] = texture;
			glActiveTexture(GL_TEXTURE0 + (int)texType); // Texture unit 1
			texture->Bind();
		}
	}
	else
	{
		SetIntTexture(objectIndex, texType);
		currentTexture[(int)texType] = texture;
		glActiveTexture(GL_TEXTURE0 + (int)texType); // Texture unit 1
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void ObjectManager::SetIntTexture(int objectIndex, TEXTURETYPE texType)
{
	switch (texType)
	{
	case TEXTURETYPE::Albedo:
		objects[objectIndex]->GetShader()->setInt("diffuseTexture", (int)texType);
		break;
	case TEXTURETYPE::Specular:
		objects[objectIndex]->GetShader()->setInt("specularTexture", (int)texType);
		break;
	case TEXTURETYPE::Normal:
		objects[objectIndex]->GetShader()->setInt("normalTexture", (int)texType);
		break;
	case TEXTURETYPE::Ambient:
		objects[objectIndex]->GetShader()->setInt("ambientTexture", (int)texType);
		break;
	case TEXTURETYPE::Rough:
		objects[objectIndex]->GetShader()->setInt("roughTexture", (int)texType);
		break;
	case TEXTURETYPE::Displacement:
		objects[objectIndex]->GetShader()->setInt("displacementTexture", (int)texType);
		break;
	default:
		break;
	}
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

bool ObjectManager::Draw(bool isBuffer)
{
	for (int i = 0; i < objects.size(); i++)
	{
		Shader* objShader = objects[i]->GetShader();
		if (objShader == nullptr)
			continue;

		Material* objMaterial = objects[i]->GetMaterial();
		if (objMaterial == nullptr)
		{
			objects[i]->Draw(projectionView);
			continue;
		}

		if (this->currentShader != objects[i]->GetShader())
		{
			objects[i]->GetShader()->Use();
			this->currentShader = objects[i]->GetShader();
			objects[i]->UpdateUniforms(projectionView, *camPos);
			UpdateLights(objShader);
		}

		if (objects[i]->isDebugObject && !isBuffer)
		{
			glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
			glBindTexture(GL_TEXTURE_2D, objects[i]->GetTexture(TEXTURETYPE::Albedo)->GetID());
			objects[i]->Draw(projectionView);
			continue;
		}
		else if (objects[i]->isDebugObject)
		{
			continue;
		}

		if (!isBuffer)
			continue;

		if (objShader->GetName() == "lightShader" && objects[i]->GetIsLight())
			objShader->setVec3("diffuseColor", pointLights[FindPointLight(objects[i])]->GetAlbedo());

		if (currentMaterial != objMaterial)
		{
			currentMaterial = objMaterial;

			for (int n = 0; n < 5; n++)
				currentTexture[n] = nullptr;

			objShader->setFloat("diffuseStrength", objMaterial->GetAlbedoStrength());
			objShader->setFloat("specularStrength", objMaterial->GetSpecularStrength());
			objShader->setFloat("normalStrength", objMaterial->GetNormalStrength());
			objShader->setFloat("ambientStrength", objMaterial->GetAmbientStrength());
			objShader->setFloat("roughStrength", objMaterial->GetRoughStrength());
			objShader->setFloat("displacementStrength", objMaterial->GetDisplacementStrength());
		}

		BindTexture(i, TEXTURETYPE::Albedo, objects[i]->GetTexture(TEXTURETYPE::Albedo));

		if (objects[i]->GetName() == "SkyBox")
		{
			glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureManager->GetSkyBox()->GetID());
			glDepthMask(GL_FALSE);
			objects[i]->Draw(projectionView);
			glDepthMask(GL_TRUE);

			continue;
		}

		BindTexture(i, TEXTURETYPE::Specular, objects[i]->GetTexture(TEXTURETYPE::Specular));
		BindTexture(i, TEXTURETYPE::Normal, objects[i]->GetTexture(TEXTURETYPE::Normal));
		BindTexture(i, TEXTURETYPE::Ambient, objects[i]->GetTexture(TEXTURETYPE::Ambient));
		BindTexture(i, TEXTURETYPE::Rough, objects[i]->GetTexture(TEXTURETYPE::Rough));
		BindTexture(i, TEXTURETYPE::Displacement, objects[i]->GetTexture(TEXTURETYPE::Displacement));

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

bool ObjectManager::FixedUpdate(float deltaTime)
{
	if (fixedUpdateFrameAmount >= fixedUpdateCount)
		return false;

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(deltaTime);
	}
	fixedUpdateCount++;
	
	return true;
}

void ObjectManager::DeleteObject(GameObject* object)
{
	// Grab all children from object.
	// Set all child objects parent to nullptr or deleted objects parent.
	// Delete object from vector.
	// Create new vector with out the deleted object.

	GameObject* newParent = nullptr;

	if (object->GetParent() != nullptr)
	{
		newParent = object->GetParent();
		newParent->RemoveChild(object);
	}

	if (object->GetChildCount() > 0)
	{
		std::vector<GameObject*> children = object->GetChildren();

		for (int i = 0; i < children.size(); i++)
			children[i]->SetParent(newParent);
	}

	int objectsIndex = FindIndex(object);
	std::vector<GameObject*> newObjectsVector;
	for (int i = 0; i < objects.size(); i++)
	{
		if (i == objectsIndex)
			continue;

		newObjectsVector.push_back(objects[i]);
	}

	objects.clear();
	objects = newObjectsVector;

	delete object;
	object = nullptr;

	SetNamesVector();
}

std::string ObjectManager::GetObjectName(int index)
{
	return Get(index)->GetName();
}