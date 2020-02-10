#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application();
	GameObject* gm = new GameObject(glm::vec3(0, -1, 0), Primitives::TYPE::Plane);
	GLFWwindow* window = glfwGetCurrentContext();

	while (glfwWindowShouldClose(window) == false)
	{
		gm->Draw(app->projectionViewMat);
		app->Update();
	}
	
	delete gm;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}