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
	void Render(float deltaTime);
	void FirstFrame();

	void MainMenuBar();
	void MaterialGUI();
	void ObjectGUI();
	void ProfilerGUI(float deltaTime);
	void HierarchyGUI();
	void ShowDummyObject(const char* prefix, int uid);

protected:
	ObjectManager* objManager = nullptr;
	MeshManager* meshManager = nullptr;
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;

	bool objectWindowVisable = false;
	bool materialWindowVisable = false;
	bool hierarchyWindowVisable = false;
	bool profilerVisable = false;

	float timerDelay = 0.0f;
	float smallest = 1000.0f;
	float largest = 0.0f;
	//Debug Vars
	float pos[3] = { 0,0,0 };
	float rot[4] = { 0,0,0,0 };
	float scale[3] = { 1,1,1 };
	float lines[30];

	std::string objName = "Testing";
	char* objNameCharP = nullptr;
	
	bool* staticBool = nullptr;
	bool* shadowCastBool = nullptr;

	std::vector<std::string> meshList;
	const char* currentMesh;

	std::vector<std::string> materialList;
	const char* currentMaterial;

	std::vector<std::string> objectList;
	int currentObject = 1;

	std::vector<std::string> shaderList;
	const char* currentShaderName;



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

	std::vector<std::string> roughList;
	const char* currentRough;
};

