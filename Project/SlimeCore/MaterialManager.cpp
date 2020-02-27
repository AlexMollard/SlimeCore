#include "MaterialManager.h"

MaterialManager::MaterialManager(TextureManager* textureManager)
{
	this->textureManager = textureManager;
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
		if (std::string(materialList[i]->name) == std::string(name))
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
bool MaterialManager::Create(std::string name, float shininess, glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor, std::string diffuseName, std::string specularName, std::string normalName, std::string ambientName)
{
	Material* mat = new Material(name.c_str(), textureManager->Get(diffuseName.c_str(), TEXTURETYPE::Diffuse), textureManager->Get(specularName.c_str(), TEXTURETYPE::Specular), textureManager->Get(normalName.c_str(), TEXTURETYPE::Normal), textureManager->Get(ambientName.c_str(), TEXTURETYPE::Ambient));
	mat->setMatAtrributes(ambientColor, diffuseColor, specularColor, shininess);
	Add(mat);
	printf("IMGUI just made a material: %s/n", name);
	return true;
}

int MaterialManager::GetIndex(std::string name)
{
	SetNames();

	for (int i = 0; i < materialNames.size(); i++)
	{
		if (materialNames[i] == name)
			return i;
	
	}
	return 404;
}

void MaterialManager::SetNames()
{
	materialNames.clear();
	for (int i = 0; i < materialList.size(); i++)
	{
		materialNames.push_back(materialList[i]->name);
	}
}

std::vector<std::string> MaterialManager::GetNames()
{
	SetNames();
	return materialNames;
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