#pragma once
#include "Mesh.h"
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	// Create / Add Functions
	//--------------------
	bool Add(Mesh* newMesh);
	bool Create(const char* name, const char* dir);
	bool Create(const char* name, Primitives::TYPE type);
	bool Create(const char* name);
	
	// Get Functions
	//--------------------
	int GetIndex(std::string name);
	Mesh* Get(std::string name, bool creation = false);
	Mesh* Get(int index);

	// Misc Functions
	//-----------------
	bool DebugManager();
	void SetNames();
	std::vector<std::string> GetNames();
	Mesh* NotFound(bool creation, std::string name = "---", int index = 404);

protected:
	// Keep track of all meshes and names for future use
	std::vector<Mesh*> meshList;
	std::vector<std::string> meshNames;
};

