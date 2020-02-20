#pragma once
#include "GameObject.h"
#include "ShaderManager.h"
#include "MaterialManager.h"

class ObjectManager
{
public:
	ObjectManager(MaterialManager* matManager, ShaderManager* shaderManager, glm::mat4* projectionView);
	~ObjectManager();

	void CreateGameObject(Mesh* mesh, int materialIndex, int shaderIndex, glm::vec3 pos = glm::vec3(0));
	void CreateGameObject(Mesh* mesh, std::string materialName, std::string shaderName, glm::vec3 pos = glm::vec3(0));
	void AddGameObject(GameObject* gameObject);
	void AddGameObjectArray(GameObject** gameObject, int amount);
	void AddGameObjectArray(std::vector<GameObject*> gameObjects);
	GameObject* GetGameObject(int index);
	GameObject* GetGameObject(std::string name);
	std::vector<GameObject*> GetGameObjectVector(int start, int end);

	bool Draw();
	bool Update(float deltaTime);

	std::vector<GameObject*> objects;
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	Shader* currentShader = nullptr;
	Texture* currentTexture = nullptr;
	glm::mat4* projectionView;
};