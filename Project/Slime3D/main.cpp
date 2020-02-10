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

using uint = unsigned int;

// Default screen res 
#define xRES 1280
#define yRES 720

// WindowSize
int windowWidth, windowHeight;

// Functions
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Update_Window(GLFWwindow* window);

// Camera
Camera camera(glm::vec3(0.0f, 2.0f, 6.0f));
float lastX = xRES / 2.0f;
float lastY = yRES / 2.0f;
bool firstMouse = true;

// MPV
glm::mat4 model;
glm::mat4 projection;
glm::mat4 view;

// DeltaTime
double last = 0.0;
double now = 0.0;
float delta = 1.0f;

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(xRES, yRES, "SlimeCore", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	windowWidth = xRES;
	windowHeight = yRES;

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Graphic Card Driver version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.15f, 0.15f, 0.15f, 1);
	glEnable(GL_DEPTH_TEST);

	const int amount = 10;
	GameObject** myObject = new GameObject * [amount];
	for (int i = 0; i < amount; i++)
	{
		myObject[i] = new GameObject(glm::vec3(i, 1, 1), glm::vec3(1), glm::vec3(1));
	}
	glm::mat4 projectionViewMat = glm::mat4(1);

	float framecount = 0.0f;

	while (glfwWindowShouldClose(window) == false)
	{
		framecount += 0.1f;
		processInput(window);
		Update_Window(window);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
		view = camera.GetViewMatrix();

		projectionViewMat = projection * view;

		for (int i = 0; i < amount; i++)
		{

			myObject[i]->SetPos(glm::vec3(glm::cos(0.5f * framecount) + i, glm::sin(0.5f * framecount), 0));

			myObject[i]->AddRotate(0.05f, glm::vec3(1.0f, 0, 0));

			myObject[i]->Draw(&projectionViewMat);
		}
	}

	for (int i = 0; i < amount; i++)
	{
		delete myObject[i];
	}
	delete[] myObject;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void Update_Window(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	now = glfwGetTime();
	delta = (float)(now - last);
	last = now;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetCurrentContext();
	glfwGetWindowSize(window, &width, &height);
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, delta);
}