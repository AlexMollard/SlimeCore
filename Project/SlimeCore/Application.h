#pragma once

#include "GameManager.h"
#include "Camera.h"
#include "DebugGUI.h"
#include "PhysicsScene.h"

class Application
{
public:
	Application(int windowWidth, int windowHeight, std::string name) { Create(windowWidth, windowHeight, name); };
	~Application();

	GLFWwindow* window = nullptr;
	using uint = unsigned int;

	// MPV
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4* projectionViewMat = nullptr;

	// DeltaTime
	double last = 0.0;
	double now = 0.0;
	float delta = 1.0f;

	// Window Size
	int appWindowWidth = 1920;
	int appWindowHeight = 1080;

	// Functions
	int Create(int windowWidth, int windowHeight, std::string name);
	void Update();
	void processInput(GLFWwindow* window);
	void Update_Window(GLFWwindow* window);
	Camera* GetCamera();
	float* GetDeltaPointer() { return &delta; };
};
