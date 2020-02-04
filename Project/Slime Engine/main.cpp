#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "FlyCamera.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shader.h"

using uint = unsigned int;

// Default screen res 
#define xRES 1280
#define yRES 720

// WindowSize
int windowWidth, windowHeight;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(xRES, yRES, "Slime Engine", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

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

	float vertices[] = {
		 0.5f,  0.5f, -0.5f,  // front top right
		 0.5f, -0.5f, -0.5f,  // front bottom right
		-0.5f, -0.5f, -0.5f,  // front bottom left
		-0.5f,  0.5f, -0.5f,  // front top left 

		 0.5f,  0.5f, 0.5f,  // back top right
		 0.5f, -0.5f, 0.5f,  // back bottom right
		-0.5f, -0.5f, 0.5f,  // back bottom left
		-0.5f,  0.5f, 0.5f   // back top left 
	};

	unsigned int indices[] = {
		0, 1, 3,   // front first triangle
		1, 2, 3,   // front second triangle

		4, 5, 7,   // back first triangle
		5, 6, 7,    // back second triangle

		4, 5, 1,   // right first triangle
		1, 0, 4,    // right second triangle

		3, 2, 6,   // left first triangle
		6, 7, 3,    // left second triangle

		0, 3, 7,   // top first triangle
		7, 4, 0,    // top second triangle

		1, 2, 6,   // bottom first triangle
		6, 5, 1    // bottom second triangle
	};

	/* Create and load mesh */
	uint VAO;
	uint VBO;
	uint IBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Camera */
	FlyCamera myCamera = FlyCamera(glm::vec3(0));
	glm::mat4 model = glm::mat4(1);
	glm::mat4 projection = myCamera.GetProjection();
	myCamera.UpdateProjectionViewTransform();
	glm::mat4 pvm = myCamera.GetProjectionView() * model;

	Shader* myShader = new Shader("..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");

	float framecount = 0.0f;
	glm::vec4 color = glm::vec4(0);
	model = glm::translate(model, glm::vec3(0.0f,0.0f,-1.0f));
	model = glm::rotate(model, 0.95f, glm::vec3(0.0f, 0.0f, 1.0f));
	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		framecount += 0.01f;

		myShader->Use();

		model = glm::rotate(model, 0.01f, glm::vec3(1.0f,0.0f,0.0f));
		color = glm::vec4(glm::sin(framecount) / 2, glm::cos(framecount) / 2, glm::tan(framecount),0);

		myShader->setMat4("projection_view_matrix", pvm);
		myShader->setMat4("model_matrix", model);
		myShader->setVec4("color", color);
		
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);

	delete myShader;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetCurrentContext();
	glfwGetWindowSize(window, &width, &height);
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}