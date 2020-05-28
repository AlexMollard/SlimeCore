#include "Application.h"
#include <stdio.h>
#include <cstdlib>
#include <sstream>

// Camera
Camera* camera = nullptr;
float lastX, lastY;
bool firstMouse = true;

// WindowSize
int windowWidth, windowHeight;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Application::Application(int windowWidth, int windowHeight, std::string name)
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Create(windowWidth, windowHeight, name);
}

Application::~Application()
{
	delete camera;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

int Application::Create(int Width, int Height, std::string name)
{
	if (glfwInit() == false)
		return -1;

	window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	lastX = Width / 2.0f;
	lastY = Height / 2.0f;

	windowWidth = Width;
	windowHeight = Height;

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Graphic Card Driver version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl << std::endl;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//V-Sync
	glfwSwapInterval(1);


	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	camera = new Camera(projection);
	projectionViewMat = &camera->ProjectionViewMat;

	return 1;
}

void Application::Update()
{
	this->appWindowWidth = windowWidth;
	this->appWindowHeight = windowHeight;
	processInput(window);
	Update_Window(window);
	camera->UpdateProjectionViewMatrix();
}

void Application::Update_Window(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	now = glfwGetTime();
	delta = (float)(now - last);
	last = now;
}

Camera* Application::GetCamera()
{
	return camera;
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

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (ImGui::IsAnyWindowFocused)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->ProcessKeyboard(FORWARD, delta);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->ProcessKeyboard(BACKWARD, delta);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->ProcessKeyboard(LEFT, delta);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->ProcessKeyboard(RIGHT, delta);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera->ProcessKeyboard(UP, delta);
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
			camera->ProcessKeyboard(DOWN, delta);

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera->MovementSpeed = 20.5f;
		else
			camera->MovementSpeed = 10.5f;

		camera->LockMouse(window, glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) != GLFW_PRESS);
	}
}