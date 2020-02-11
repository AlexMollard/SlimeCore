#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application();
	GameObject* gm = new GameObject(glm::vec3(0, -1, 0), Primitives::TYPE::Cube);
	GameObject* gm2 = new GameObject(glm::vec3(2, -1, 0), Primitives::TYPE::Cube);
	GameObject* gm3 = new GameObject(glm::vec3(-2, -1, 0), Primitives::TYPE::Cube);
	GameObject* gm4 = new GameObject(glm::vec3(4, -1, 0), Primitives::TYPE::Cube);
	GameObject* gm5 = new GameObject(glm::vec3(-4, -1, 0), Primitives::TYPE::Cube);
	GLFWwindow* window = glfwGetCurrentContext();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float timer = 0.0f;
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.05f;
		
		gm->SetPos(glm::vec3(0,glm::cos(timer),0));
		gm->Draw(app->projectionViewMat);

		gm2->SetPos(glm::vec3(2, glm::cos(timer + 0.05f), 0));
		gm2->Draw(app->projectionViewMat);

		gm3->SetPos(glm::vec3(-2, glm::cos(timer + 0.1f), 0));
		gm3->Draw(app->projectionViewMat);

		gm4->SetPos(glm::vec3(4, glm::cos(timer + 0.15f), 0));
		gm4->Draw(app->projectionViewMat);

		gm5->SetPos(glm::vec3(-4, glm::cos(timer + 0.2f), 0));
		gm5->Draw(app->projectionViewMat);
		app->Update();
	}
	
	delete gm;
	delete gm2;
	delete gm3;
	delete gm4;
	delete gm5;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}