#pragma once
#include "ObjectManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class DebugGUI
{
public:
	DebugGUI(ObjectManager* objManager, MeshManager* meshManager, MaterialManager* materialManager, TextureManager* textureManager, ShaderManager* shaderManager);
	~DebugGUI();

	// Must run before first render to set default values 
	// (Has to be after all managers are finished being set and populated) 
	void FirstFrame();

	// Render all windows and main menu bar
	void Render(float deltaTime);

	// Render Main Menu Bar
	void MainMenuBar();

	// Windows
	void MaterialGUI();
	void ProfilerGUI(float deltaTime);
	void HierarchyGUI();

	// Used in hierarchy window to get children
	void ShowChildObject(const char* prefix, int uid);

private:

	// Managers
	ObjectManager* objManager = nullptr;
	MeshManager* meshManager = nullptr;
	MaterialManager* matManager = nullptr;
	ShaderManager* shaderManager = nullptr;
	TextureManager* textureManager = nullptr;

	// Window Visibility
	bool materialWindowVisable = false;
	bool hierarchyWindowVisable = false;
	bool profilerVisable = false;

	//----------------------------------
	// Profiler Window Variables
	//----------------------------------

	// FPS variables
	float lines[30];
	float fpsTotal = 0.0f;
	float timerDelay = 0.0f;
	float smallest = 1000.0f;
	float largest = 0.0f;
	float currentFPS = 0.0f;
	int fpsCount = 0;

	//----------------------------------
	// Hierarchy Window Variables
	//----------------------------------
	
	// Default Object Vars
	float pos[3] = { 0,0,0 };
	float rot[4] = { 0,0,0,0 };
	float scale[3] = { 1,1,1 };

	// Object Name
	std::string objName = "Testing";
	char* objNameCharP = nullptr;
	
	// Object bools (Static / CastShadows)
	bool* staticBool = nullptr;
	bool* shadowCastBool = nullptr;

	// Mesh List (Char*)
	std::vector<std::string> meshList;
	const char* currentMesh;

	// Material List (Char*)
	std::vector<std::string> materialList;
	const char* currentMaterial;
	const char* currentEditorMaterial;

	// Shader List (Char*)
	std::vector<std::string> shaderList;
	const char* currentShaderName;

	// Object List (Int)
	std::vector<std::string> objectList;
	int currentObject = 1;

	//----------------------------------
	// Create Material Window Variables
	//----------------------------------

	// Material Name
	std::string matName = "Testing";
	char* matNameCharP = nullptr;

	// Diffuse
	std::vector<std::string> diffuseList;
	const char* currentDiffuse;
	float diffuseStrength = 1;

	// Specular
	std::vector<std::string> specularList;
	const char* currentSpecular;
	float specularStrength = 1;

	// Normal
	std::vector<std::string> normalList;
	const char* currentNormal;
	float normalStrength = 1;

	// Ambient
	std::vector<std::string> ambientList;
	const char* currentAmbient;
	float ambientStrength = 1;

	// Rough
	std::vector<std::string> roughList;
	const char* currentRough;
	float roughStrength = 1;
};

