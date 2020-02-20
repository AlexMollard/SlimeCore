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

Material* MaterialManager::GetMaterialByName(bool creation, const char* name)
{
	for (int i = 0; i < materialList.size(); i++)
	{
		if (materialList[i]->name == name)
		{
			return materialList[i];
		}
	}

	return MaterialNotFound(creation, name);
}

Material* MaterialManager::GetMaterialByIndex(int index)
{
	return materialList[index] ? materialList[index] : MaterialNotFound(false, "---",index);
}

bool MaterialManager::CreateMaterial(const char* name, Texture* texture)
{
	if (GetMaterialByName(true,name) == nullptr)
	{
		printf("Creating Material with name: %s.\n", name);
		AddMaterial(new Material(name, texture));
		return true;
	}

	printf("Material already exist with name: %s.\n", name);
	return false;
}

Material* MaterialManager::MaterialNotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Material Not Found with name: %s, index: %d.\n", name, index);
	
	return nullptr;
}

bool MaterialManager::AddMaterial(Material* newMaterial)
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