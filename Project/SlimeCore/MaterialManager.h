#pragma once
#include "Material.h"
#include <vector>
#include "TextureManager.h"

class MaterialManager
{
public:
	MaterialManager(TextureManager* textureManager);
	~MaterialManager();

	Material* Get(const char* name, bool creation = false);
	Material* Get(int index);

	Material* NotFound(bool creation, const char* name = "---", int index = 404);
	bool Add(Material* newMaterial);
	bool Create(const char* name, Texture* diffuse);
	bool Create(const char* name, Texture* diffuse, Texture* specular, Texture* normal, Texture* ambient);
	void Create(std::string name, float shininess, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, std::string diffuseName, std::string specularName = "none", std::string normalName = "none", std::string ambientName = "none");
	int GetIndex(std::string name);
	void SetNames();
	std::vector<std::string> GetNames();

	void SetSpotLightPos(glm::vec3 lightOne, glm::vec3 lightTwo, glm::vec3 lightThree, glm::vec3 lightFour);
	void SetDirLightDirection(glm::vec3 direction);

	bool DebugManager();
protected:
	TextureManager* textureManager = nullptr;
	std::vector<Material*> materialList;
	std::vector<std::string> materialNames;
};

