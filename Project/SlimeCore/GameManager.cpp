#include "GameManager.h"

GameManager::GameManager(Camera* mainCamera)
{
	camera = mainCamera;
	shaderManager = new ShaderManager();
	materialManager = new MaterialManager();
	textureManager = new TextureManager();
	objectManager = new ObjectManager(materialManager, shaderManager, textureManager, &camera->GetProjectionViewMatrix(), &camera->Position);
}

GameManager::~GameManager()
{
	delete shaderManager;
	delete materialManager;
	delete textureManager;
	delete objectManager;
}
