#include "MeshManager.h"

MeshManager::MeshManager()
{
	Create("None");
}

MeshManager::~MeshManager()
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i] != nullptr)
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}
}

Mesh* MeshManager::Get(std::string name, bool creation)
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

Mesh* MeshManager::NotFound(bool creation, std::string name, int index)
{
	if (!creation)
		printf("Mesh Not Found with name: %s, index: %d.\n", name.c_str(), index);

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
		Add(new Mesh(name));
		meshList.back()->create(type);
		return true;
	}

	printf("Mesh already exist with name: %s.\n", name);
	return false;
}

bool MeshManager::Create(const char* name)
{
	if (Get(name, true) == nullptr)
	{
		Add(new Mesh(name));
		return true;
	}

	printf("Mesh already exist with name: %s.\n", name);
	return false;
}

int MeshManager::GetIndex(std::string name)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i]->GetName() == name)
			return i;
	}

	printf("Cant Find index for that mesh");
	return -404;
}

int MeshManager::GetIndex(Mesh* name)
{
	for (int i = 0; i < meshList.size(); i++)
	{
		if (meshList[i] == name)
			return i;
	}

	printf("Cant Find index for that mesh");
	return -404;
}

void MeshManager::SetNames()
{
	meshNames.clear();
	for (int i = 0; i < meshList.size(); i++)
	{
		meshNames.push_back(meshList[i]->GetName());
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
		std::cout << " - " << meshList[i]->GetName() << std::endl;
	}
	printf("\n");

	return true;
}
