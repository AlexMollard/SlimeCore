#pragma once
#include "Material.h"
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
	bool Create(std::string name, Texture* diffuse);
	bool Create(std::string name, Texture* diffuse, Texture* specular, Texture* normal, Texture* ambient, Texture* rough);
	void Create(std::string name, std::string diffuseName, std::string specularName, std::string normalName, std::string ambientName, std::string roughName);
	void Create(std::string name, std::string diffuseName, float diffuseStrength, std::string specularName, float specularStrength, std::string normalName, float normalStrength, std::string ambientName, float ambientStrength, std::string roughName, float roughStrength);
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

