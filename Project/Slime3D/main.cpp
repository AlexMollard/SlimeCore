#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application();
	GLFWwindow* window = glfwGetCurrentContext();

	Texture* grass = new Texture("..\\Images\\grass.png");
	Texture* dirt = new Texture("..\\Images\\dirt.png");
	Texture* water = new Texture("..\\Images\\water.png");
	Texture* light = new Texture("..\\Images\\light.png");

	const int num = 25;
	GameObject* ground[num][num];

	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < num; y++)
		{
			float simplexNoise = glm::simplex(glm::vec2(x / 4.9f, y / 4.9f));
			ground[x][y] = new GameObject(glm::vec3(
				(x - (num / 2)) * 2.0f ,
				simplexNoise < 0.15f ? -3.2f : simplexNoise > 0.6f ? -1.2f : -3.0f,
				(y - (num / 2)) * 2.0f ),
				Primitives::TYPE::Cube,
				simplexNoise > 0.2f ? grass : simplexNoise > 0.10f ? dirt : water, 0.5f,0.65f,50);
		}
	}

	glm::vec3 lightPos = glm::vec3(0,1,0);
	GameObject* lightOB = new GameObject(lightPos, Primitives::TYPE::Cube, light);
	lightOB->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	float timer = 0.0f;
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.05f;
		
		lightPos = glm::vec3(glm::cos(timer/2) * 10,1,glm::sin(timer/2) * 10);
		lightOB->SetPos(lightPos);
		lightOB->Draw(app->projectionViewMat, app->GetCamera(), lightPos);

		for (int x = 0; x < num; x++)
		{
			for (int y = 0; y < num; y++)
			{
				ground[x][y]->Draw(app->projectionViewMat, app->GetCamera(), lightPos);
			}
		}

		app->Update();
	}

	delete lightOB;
	
	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < num; y++)
		{
			delete ground[x][y];
		}
	}
	delete grass;
	delete dirt;
	delete water;
	delete light;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}