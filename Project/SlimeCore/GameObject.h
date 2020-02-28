#pragma once
#include "glm.hpp"
#include "Mesh.h"
#include "Types.h"
#include "Shader.h"
#include "Material.h"

class GameObject
{
public:
	GameObject(std::string name, Mesh* mesh, Material* mat, Shader* shader);

	virtual ~GameObject();

	glm::mat4 GetModel();
	void Update(float deltaTime);
	void Draw(glm::mat4* ProjectionView = nullptr);
	void UpdateUniforms(glm::mat4* ProjectionView, glm::vec3 cameraPos);

	void SetPos(glm::vec3 newPos);
	glm::vec3 GetPos();
	void AddRotate(float rotSpeed, glm::vec3 rotDIR);
	void SetScale(glm::vec3 newScale);

	Mesh* GetMesh() { return mesh; };
	Material* GetMaterial() { return mat; };
	Texture* GetTexture(TEXTURETYPE type);
	std::string name = "Default GameObject";
	bool isSkyBox = false;
	Shader* shader = nullptr;
protected:
	glm::vec3 position = glm::vec3(1);
	glm::vec3 rotation = glm::vec3(1);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 model = glm::mat4(1);
	Material* mat = nullptr;
	Mesh* mesh = nullptr;
};

