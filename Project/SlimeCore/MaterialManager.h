#pragma once
#include "Material.h"
#include <vector>
class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	Material* GetMaterialByName(bool creation, const char* name);
	Material* GetMaterialByIndex(int index);

	Material* MaterialNotFound(bool creation, const char* name = "---", int index = 404);
	bool AddMaterial(Material* newMaterial);
	bool CreateMaterial(const char* name, Texture* texture);

	bool DebugManager();

protected:
	std::vector<Material*> materialList;
};

