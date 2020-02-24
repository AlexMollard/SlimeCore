#include "MaterialManager.h"

MaterialManager::MaterialManager()
{
}

MaterialManager::~MaterialManager()
{
	printf("Deleteing MaterialManager:\n");

	for (int i = 0; i < materialList.size(); i++)
	{
		if (materialList[i] != nullptr)
		{
			printf(" - Deleteing material: %s.\n", materialList[i]->name);
			delete materialList[i];
			materialList[i] = nullptr;
		}
	}
	printf("\n");
}

Material* MaterialManager::Get(const char* name, bool creation)
{
	for (int i = 0; i < materialList.size(); i++)
	{
		if (materialList[i]->name == name)
		{
			return materialList[i];
		}
	}

	return NotFound(creation, name);
}

Material* MaterialManager::Get(int index)
{
	return materialList[index] ? materialList[index] : NotFound(false, "---",index);
}

bool MaterialManager::Create(const char* name, Texture* texture)
{
	if (Get(name,true) == nullptr)
	{
		printf("Creating Material with name: %s.\n", name);
		Add(new Material(name, texture));
		return true;
	}

	printf("Material already exist with name: %s.\n", name);
	return false;
}

Material* MaterialManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Material Not Found with name: %s, index: %d.\n", name, index);
	
	return nullptr;
}

bool MaterialManager::Add(Material* newMaterial)
{
	materialList.push_back(newMaterial);
	return true;
}

bool MaterialManager::DebugManager()
{
	printf("Materials: \n");
	for (int i = 0; i < materialList.size(); i++)
	{
		std::cout << " - " << materialList[i]->name << std::endl;
	}
	printf("\n");

	return true;
}