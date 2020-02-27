#include "MeshManager.h"

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	printf("Deleteing MeshManager:\n");

	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i] != nullptr)
		{
			printf(" - Deleteing mesh: %s.\n", meshList[i]->name);
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}
	printf("\n");
}

Mesh* MeshManager::Get(const char* name, bool creation)
{
	SetNames();
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshNames[i] == std::string(name))
		{
			return meshList[i];
		}
	}

	return NotFound(creation, name);
}

Mesh* MeshManager::Get(int index)
{
	return meshList[index] ? meshList[index] : NotFound(false, "---", index);
}

Mesh* MeshManager::NotFound(bool creation, const char* name, int index)
{
	if (!creation)
		printf("Mesh Not Found with name: %s, index: %d.\n", name, index);

	return nullptr;
}

bool MeshManager::Add(Mesh* newMesh)
{
	meshList.push_back(newMesh);
	return true;
}

bool MeshManager::Create(const char* name, const char* dir)
{
	if (Get(name, true) == nullptr)
	{
		printf("Creating Mesh with name: %s.\n", name);
		Add(new Mesh(name, dir));
		return true;
	}

	printf("Mesh already exist with name: %s.\n", name);
	return false;
}

bool MeshManager::Create(const char* name, Primitives::TYPE type)
{
	if (Get(name, true) == nullptr)
	{
		//printf("Creating Mesh with name: %s.\n", name);
		Add(new Mesh(name));
		meshList.back()->create(type);
		return true;
	}

	printf("Mesh already exist with name: %s.\n", name);
	return false;
}

int MeshManager::GetIndex(std::string name)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i]->name == name)
			return i;
	}

	printf("Cant Find index for that mesh");
	return 404;
}

void MeshManager::SetNames()
{
	meshNames.clear();
	for (int i = 0; i < meshList.size(); i++)
	{
		meshNames.push_back(meshList[i]->name);
	}
}

std::vector<std::string> MeshManager::GetNames()
{
	SetNames();
	return meshNames;
}

bool MeshManager::DebugManager()
{
	printf("Meshes: \n");
	for (int i = 0; i < meshList.size(); i++)
	{
		std::cout << " - " << meshList[i]->name << std::endl;
	}
	printf("\n");

	return true;
}
