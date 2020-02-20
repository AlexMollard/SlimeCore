#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "MaterialManager.h"
#include "ShaderManager.h"
#include "Mesh.h"
#include "Camera.h"
class GameObject
{
public:
	GameObject(Mesh* mesh, Material* mat, Shader* shader);

	virtual ~GameObject();

	glm::mat4 GetModel();
	void Update(float deltaTime);
	void Draw(glm::mat4* ProjectionView = nullptr);
	void UpdateUniforms(glm::mat4* ProjectionView);

	void SetPos(glm::vec3 newPos);
	void AddRotate(float rotSpeed, glm::vec3 rotDIR);
	void SetScale(glm::vec3 newScale);

	Mesh* GetMesh() { return mesh; };
	Material* GetMaterial() { return mat; };
	Texture* GetTexture() { return mat->GetTexture(); };
	Shader* shader = nullptr;
	std::string name = "Default";
protected:
	glm::vec3 position = glm::vec3(1);
	glm::vec3 rotation = glm::vec3(1);
	glm::vec3 scale = glm::vec3(1);

	glm::mat4 model = glm::mat4(1);
	Material* mat = nullptr;
	Mesh* mesh = nullptr;
};

