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

	glm::mat4 GetModel();
	void Update(float deltaTime);
	void Draw(glm::mat4* ProjectionView = nullptr);
	void UpdateUniforms(glm::mat4* ProjectionView, glm::vec3 cameraPos);

	void SetPos(glm::vec3 newPos);
	glm::vec3 GetPos();
	void AddRotate(float rotSpeed, glm::vec3 rotDIR);
	void SetScale(glm::vec3 newScale);
	glm::vec3 GetScale();
	bool GetIsLight();
	Mesh* GetMesh() { return mesh; };
	void SetMesh(Mesh* newMesh);
	Material* GetMaterial() { return mat; };
	void SetMaterial(Material* newMaterial);
	Texture* GetTexture(TEXTURETYPE type);
	Shader* GetShader();
	void SetShader(Shader* newShader);
	std::string GetName();
	void SetName(std::string newName);
	std::string GetDescription();
	void SetDescription(std::string newDesc);
	void SetIsLight(bool value);
	GameObject* GetChild(int index);
	GameObject* GetChild(std::string name);
	std::vector<GameObject*> GetChildren();
	int GetChildCount();
	void AddChild(GameObject* newChild);
	void RemoveChild(GameObject* oldChild);
	int FindChild(GameObject* childToFind);
	void SetParent(GameObject* newParent);
	GameObject* GetParent();
protected:
	Shader* shader = nullptr;
	std::string name = "Default GameObject";
	bool isPointLight = false;

	glm::vec3 position = glm::vec3(1);
	glm::vec3 rotation = glm::vec3(1);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 model = glm::mat4(1);
	Material* mat = nullptr;
	Mesh* mesh = nullptr;
	std::string description = "Default Description";
	std::vector<GameObject*> child;
	GameObject* parent = nullptr;
};

