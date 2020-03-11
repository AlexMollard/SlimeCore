#pragma once
#include "glm.hpp"
#include "Mesh.h"
#include "Types.h"
#include "Shader.h"
#include "Material.h"

class GameObject
{
public:
	GameObject();
	GameObject(std::string name, Mesh* mesh, Material* mat, Shader* shader, GameObject* parent = nullptr);
	
	virtual ~GameObject();

	// Transform Functions
	//-------------------
	glm::mat4 GetModel();
	void SetPos(glm::vec3 newPos);
	glm::vec3 GetPos();
	void SetScale(glm::vec3 newScale);
	glm::vec3 GetScale();
	void AddRotate(float rotSpeed, glm::vec3 rotDIR);	//Broken
	void SetRotate( glm::vec3 rotation);	//Broken
	void SetSkyBoxPos(glm::vec3* newPos);

	// Frame Functions
	//-------------------
	void Update(float deltaTime);
	void Draw(glm::mat4* ProjectionView = nullptr);

	// Shader Functions
	//-------------------
	void SetShader(Shader* newShader);
	Shader* GetShader();
	void UpdateUniforms(glm::mat4* ProjectionView, glm::vec3 cameraPos);

	// Material Functions
	//-------------------
	void SetMaterial(Material* newMaterial);
	Material* GetMaterial() { return mat; };
	Texture* GetTexture(TEXTURETYPE type);

	// Mesh Functions
	//-------------------
	void SetMesh(Mesh* newMesh);
	Mesh* GetMesh() { return mesh; };

	// PointLight Functions
	//-------------------
	void SetIsLight(bool value);
	bool GetIsLight();

	// Child Functions
	//-------------------
	void AddChild(GameObject* newChild);
	int FindChild(GameObject* childToFind);
	int GetChildCount();
	GameObject* GetChild(int index);
	GameObject* GetChild(std::string name);
	std::vector<GameObject*> GetChildren();
	void RemoveChild(GameObject* oldChild);

	// Parent Functions
	//-------------------
	void SetParent(GameObject* newParent);
	GameObject* GetParent();

	// Misc Functions
	//-------------------
	void SetName(std::string newName);
	std::string GetName();
	void SetDescription(std::string newDesc);
	std::string GetDescription();

protected:
	// Misc
	std::string name = "Default GameObject";
	std::string description = "Default Description";
	
	// Refrences
	Shader* shader = nullptr;
	Material* mat = nullptr;
	Mesh* mesh = nullptr;

	// Object Refrences
	GameObject* parent = nullptr;
	std::vector<GameObject*> child;
	
	// Transform Variables
	glm::mat4 model = glm::mat4(1);
	glm::vec3 position = glm::vec3(1);
	glm::vec3 rotation = glm::vec3(1);
	glm::vec3 scale = glm::vec3(1);

	// PointLight Variables
	bool isPointLight = false;
};

