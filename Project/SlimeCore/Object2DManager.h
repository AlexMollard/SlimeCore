#pragma once
#include "ObjectManager.h"
#include "GameObject2D.h"
class Object2DManager
{
public:
	Object2DManager(TextureManager* textureManager);
	~Object2DManager();

	GameObject2D* CreateBox(glm::vec3 Position = glm::vec3(0), float width = 1.0f, float height = 1.0f);
	GameObject2D* CreateLine(glm::vec3 startPosition, glm::vec3 endPosition, float width = 1.0f);
	GameObject2D* CreateCircle(glm::vec3 Position = glm::vec3(0), float Diameter = 1.0f);

	void SetUpSpriteMesh(GameObject2D* currentObject, glm::vec3 topLeft, glm::vec3 bottomLeft, glm::vec3 topRight, glm::vec3 bottomRight);
	void CreateMesh(GameObject2D* currentObject);
	void Draw();
	void Update(float deltaTime);
	std::vector<GameObject2D*> GetAllObjects();

protected:
	std::vector<GameObject2D*> objects;
	glm::mat4 orthoMatrix = glm::ortho<float>(-16, 16, -9, 9, -1, 1);
	TextureManager* texManager;
	Shader* TwoDShader = nullptr;
	Texture* defaultWhite = nullptr;
	Texture* currentTexture = nullptr;
	Texture* defaultCircleTexture = nullptr;
};