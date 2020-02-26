#pragma once
#include "ObjectManager.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class DebugGUI
{
public:
	DebugGUI(ObjectManager* objManager);
	~DebugGUI();
	void Render();
	void FirstFrame();

	void MeshGUI();
	void MaterialGUI();
	void ShaderGUI();

protected:
	ObjectManager* objManager = nullptr;

	//Debug Vars
	std::string TextBoxString;
	char* cstr = nullptr;
	
	bool* staticBool = nullptr;
	bool* shadowCastBool = nullptr;

	std::vector<std::string> componentList;
	const char* currentComponent;

	// Material tab
	std::vector<std::string> diffuseList;
	const char* currentDiffuse;

	std::vector<std::string> specularList;
	const char* currentSpecular;
};

