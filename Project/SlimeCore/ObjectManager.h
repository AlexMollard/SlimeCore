#pragma once
#include "GameObject.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "TextureManager.h"

class ObjectManager
{
public:
	ObjectManager(MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* cameraPos);
	~ObjectManager();

	void Create(std::string name, Mesh* mesh, int materialIndex, int shaderIndex, glm::vec3 pos = glm::vec3(0));
	void Create(std::string name, Mesh* mesh, std::string materialName, std::string shaderName, glm::vec3 pos = glm::vec3(0));
	void Swap(int objIndex, int vectorPos);
	void Add(GameObject* gameObject);
	void AddArray(GameObject** gameObject, int amount);
	void AddArray(std::vector<GameObject*> gameObjects);
	int FindIndex(GameObject* object);
	int FindIndex(std::string name);
	void MoveObject(GameObject* obj, int newPos);
	GameObject* Get(int index);
	GameObject* Get(std::string name);
	std::vector<GameObject*> GetVector(int start, int end);

	void SetNamesVector();
	std::vector<const char*> GetNameVector();

	bool DebugManager();
	bool DebugAll();

	bool Draw();
	bool Update(float deltaTime);

	std::vector<GameObject*> objects;
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	TextureManager* textureManager = nullptr;
	Shader* currentShader = nullptr;
	Texture* currentTexture = nullptr;
	glm::mat4* projectionView;
	std::vector<const char*> names;
	glm::vec3* camPos;
};