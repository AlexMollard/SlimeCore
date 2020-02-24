#pragma once
#include "Material.h"
#include <vector>
class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	Material* Get(const char* name, bool creation = false);
	Material* Get(int index);

	Material* NotFound(bool creation, const char* name = "---", int index = 404);
	bool Add(Material* newMaterial);
	bool Create(const char* name, Texture* texture);

	bool DebugManager();
protected:
	std::vector<Material*> materialList;
};

