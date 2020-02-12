#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application();

	Texture* slime = new Texture("..\\Images\\test.png");
	Texture* grass = new Texture("..\\Images\\grass.png");
	Texture* water = new Texture("..\\Images\\water.jpg");
	Texture* dirt = new Texture("..\\Images\\dirt.jpg");

	GameObject* gm = new GameObject(glm::vec3(0, 0, 1), Primitives::TYPE::Cube, slime);
	GameObject* gm2 = new GameObject(glm::vec3(2, 0, 1), Primitives::TYPE::Cube, slime);
	GameObject* gm3 = new GameObject(glm::vec3(-2, 0, 1), Primitives::TYPE::Cube, slime);
	GameObject* gm4 = new GameObject(glm::vec3(4, 0, 1), Primitives::TYPE::Cube, slime);
	GameObject* gm5 = new GameObject(glm::vec3(-4, 0, 1), Primitives::TYPE::Cube, slime);


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
				simplexNoise > 0.6f ? grass : simplexNoise > 0.15f ? dirt : water);
		}
	}

	GLFWwindow* window = glfwGetCurrentContext();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float timer = 0.0f;
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.05f;
		
		gm->SetPos(glm::vec3(0,glm::cos(timer),0));
		gm->Draw(app->projectionViewMat);

		gm2->SetPos(glm::vec3(2.5f, glm::cos(timer + 0.05f), 0));
		gm2->Draw(app->projectionViewMat);

		gm3->SetPos(glm::vec3(-2.5f, glm::cos(timer + 0.1f), 0));
		gm3->Draw(app->projectionViewMat);

		gm4->SetPos(glm::vec3(5, glm::cos(timer + 0.15f), 0));
		gm4->Draw(app->projectionViewMat);

		gm5->SetPos(glm::vec3(-5, glm::cos(timer + 0.2f), 0));
		gm5->Draw(app->projectionViewMat);

		for (int x = 0; x < num; x++)
		{
			for (int y = 0; y < num; y++)
			{
				ground[x][y]->Draw(app->projectionViewMat);
			}
		}

		app->Update();
	}
	
	delete gm;
	delete gm2;
	delete gm3;
	delete gm4;
	delete gm5;

	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < num; y++)
		{
			delete ground[x][y];
		}
	}
	delete slime;
	delete grass;
	delete dirt;
	delete water;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}