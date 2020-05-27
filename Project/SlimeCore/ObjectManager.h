#pragma once
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ShaderManager.h"
#include "MaterialManager.h"
#include "MeshManager.h"

class ObjectManager
{
public:
	ObjectManager() {};
	ObjectManager(MeshManager* meshManager, MaterialManager* matManager, ShaderManager* shaderManager, TextureManager* textureManager, glm::mat4* projectionView, glm::vec3* cameraPos);
	~ObjectManager();

	// Every Frame Functions
	//------------------
	bool Draw(bool isBuffer = false);
	bool Update(float deltaTime);
	bool FixedUpdate(float deltaTime);

	// Create / Add Functions
	//------------------
	GameObject* Create(GameObject* parent, std::string name);
	GameObject* Create(std::string name, int meshIndex, int materialIndex, int shaderIndex, int parent = 0, glm::vec3 pos = glm::vec3(0));
	GameObject* Create(std::string name, Primitives::TYPE type, int materialIndex, int shaderIndex, int parent = 0, glm::vec3 pos = glm::vec3(0));
	GameObject* Create(std::string name, std::string meshName, std::string materialName, std::string shaderName, std::string parent, glm::vec3 pos = glm::vec3(0));
	void Add(GameObject* gameObject);
	void Add(GameObject** gameObject, int amount);
	void Add(std::vector<GameObject*> gameObjects);

	// Get Functions
	//------------------
	GameObject* Get(int index);
	GameObject* Get(std::string name);
	std::vector<GameObject*> Get(int start, int end);
	int FindIndex(GameObject* object);
	int FindIndex(std::string name);
	int GetObjectSize();

	// Delete Object Functions
	//------------------
	void DeleteObject(GameObject* object);

	// Light Functions
	//------------------
	int FindPointLight(GameObject* lightObject);
	PointLight* CreatePointLight(std::string name, glm::vec3 pos, GameObject* parent = nullptr);
	void AddPointLight(PointLight* light);

	void CreateDirectionalLight();

	void UpdateLights(Shader* shader);

	// Misc Functions
	//------------------
	void SetVars(int index, std::string name, bool isStatic, glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale, std::string meshName, std::string materialName, std::string shaderName);
	void Swap(int objIndex, int vectorPos);
	bool DebugManager();
	bool DebugAll();

	// Name Functions
	//------------------
	void SetNamesVector();
	std::vector<std::string> GetNameVector();
	std::string GetObjectName(int index);

	// Render Functions
	//------------------
	void BindTexture(int objectIndex, TEXTURETYPE type, Texture* texture);
	void SetIntTexture(int objectIndex, TEXTURETYPE type);

	//protected:
		// Objects
	std::vector<GameObject*> objects;
	std::vector<std::string> names;
	std::vector<PointLight*> pointLights;
	DirectionalLight* directionalLight;

	// Managers
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	TextureManager* textureManager = nullptr;
	MeshManager* meshManager = nullptr;

	// Current Variables to check to save un needed binds
	Shader* currentShader = nullptr;
	Material* currentMaterial = nullptr;
	Texture* currentTexture[6] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };

	// Misc Variables
	glm::mat4* projectionView;
	glm::vec3* camPos;

	int fixedUpdateCount = 0;
	int fixedUpdateFrameAmount = 2;
};