#pragma once
#include "Material.h"

class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	Material* GetMaterialByName(bool creation, const char* name);
	Material* GetMaterialByIndex(int index);

	Material* MaterialNotFound(bool creation, const char* name = "---", int index = 404);
	bool AddMaterial(Material* newMaterial);
	bool CreateMaterial(const char* name, Shader* shader, Texture* texture);

	bool DebugManager();

protected:
	std::vector<Material*> materialList;
};

