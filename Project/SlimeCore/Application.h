#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Camera.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "GameObject.h"

// Default screen res 
#define xRES 1280
#define yRES 720

class Application
{
public:
	Application() { Create(); };
	~Application();
	int Create();

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


	// Functions
	void Update();
	void processInput(GLFWwindow* window);
	void Update_Window(GLFWwindow* window);
};

