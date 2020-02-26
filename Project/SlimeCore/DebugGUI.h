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

protected:
	ObjectManager* objManager = nullptr;

	//Debug Vars
	int currentCubeIndex = 0;
	GameObject* currentGameObject = nullptr;
	glm::vec3 currentPOS = glm::vec3(0, 2, 0);
	std::vector<const char*> names;
	int currentName = 0;
	Mesh* cube = nullptr;
};

