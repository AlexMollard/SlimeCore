#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"

using uint = unsigned int;

int main()
{
	if (glfwInit() == false)
		return -1;

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Slime Engine", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}
	
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	glClearColor(0.15f, 0.15f, 0.15f, 1);
	glEnable(GL_DEPTH_TEST);

	glm::vec3 vertices[] =
	{
		glm::vec3(-0.5f,0.5f,0.0f) ,
		glm::vec3(0.5f,0.5f,0.0f),
		glm::vec3(-0.5f,-0.5f,0.0f),
		glm::vec3(0.5f,0.5f,0.0f),
		glm::vec3(-0.5f,-0.5f,0.0f),
		glm::vec3(0.5f,-0.5f,0.0f)
	};

	glm::mat4 Projection = glm::perspective(90.0f, 16 / 9.0f, 0.1f, 5.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0,0,1), glm::vec3(0,0,0), glm::vec3(0,1,0));
	glm::mat4 model = glm::mat4(1);

	glm::mat4 pvm = Projection * view * model;

	for (int i = 0; i < 6; i++)
	{
		vertices[i] = glm::vec3(pvm * glm::vec4(vertices[i], 1));
	}

	uint VAO;
	uint VBO;
	// int IBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	while (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		//Game Loop
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}