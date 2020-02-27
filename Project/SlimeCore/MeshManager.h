#pragma once
#include "Mesh.h"
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	Mesh* Get(const char* name, bool creation = false);
	Mesh* Get(int index);

	Mesh* NotFound(bool creation, const char* name = "---", int index = 404);
	bool Add(Mesh* newMesh);
	bool Create(const char* name, const char* dir);
	bool Create(const char* name, Primitives::TYPE type);

	int GetIndex(std::string name);

	void SetNames();
	std::vector<std::string> GetNames();

	bool DebugManager();
protected:
	std::vector<Mesh*> meshList;
	std::vector<std::string> meshNames;
};

