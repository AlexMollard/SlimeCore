#pragma once
#include "ObjectManager.h"
#include "GameObject2D.h"
class Object2DManager : public ObjectManager
{
public:
	Object2DManager(TextureManager* textureManager);
	~Object2DManager();

	GameObject2D* CreateBox(glm::vec3 Position = glm::vec3(0), float xWidth = 1.0f, float yWidth = 1.0f);
	void CreateMesh(GameObject2D* currentObject);

	void Draw();

protected:
	std::vector<GameObject2D*> objects;
	glm::mat4 orthoMatrix = glm::ortho<float>(-16, 16, -9, 9, -1, 1);
	TextureManager* texManager;
	Shader* TwoDShader = nullptr;
	Texture* defaultWhite = nullptr;
	Texture* currentTexture = nullptr;
};

