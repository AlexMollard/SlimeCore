#pragma once
#include"MaterialManager.h"
#include"ShaderManager.h"
#include"TextureManager.h"
#include"ObjectManager.h"

class GameManager
{
public:
	GameManager(Camera* mainCamera);
	~GameManager();

	Camera* camera = nullptr;
	MaterialManager* materialManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	TextureManager* textureManager = nullptr;
	ObjectManager* objectManager = nullptr;
};
