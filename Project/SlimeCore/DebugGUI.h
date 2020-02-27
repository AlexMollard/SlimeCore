#pragma once
#include "ObjectManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class DebugGUI
{
public:
	DebugGUI(ObjectManager* objManager, MeshManager* meshManager);
	~DebugGUI();
	void Render();
	void FirstFrame();

	void MaterialGUI();
	void ObjectGUI();

protected:
	ObjectManager* objManager = nullptr;
	MeshManager* meshManager = nullptr;
	MaterialManager* matManager = nullptr;

	//Debug Vars
	float pos[3] = { 0,0,0 };
	float rot[4] = { 0,0,0,0 };
	float scale[3] = { 1,1,1 };

	std::string objName = "Testing";
	char* objNameCharP = nullptr;
	
	bool* staticBool = nullptr;
	bool* shadowCastBool = nullptr;

	std::vector<std::string> meshList;
	const char* currentMesh;

	std::vector<std::string> materialList;
	const char* currentMaterial;


	// Material tab
	std::string matName = "Testing";
	char* matNameCharP = nullptr;

	float* shininess = new float(1);
	float ambColor[3] = { 1,1,1 };
	float difColor[3] = { 1,1,1 };
	float specColor[3] = { 1,1,1 };

	std::vector<std::string> diffuseList;
	const char* currentDiffuse;

	std::vector<std::string> specularList;
	const char* currentSpecular;

	std::vector<std::string> normalList;
	const char* currentNormal;

	std::vector<std::string> ambientList;
	const char* currentAmbient;
};

