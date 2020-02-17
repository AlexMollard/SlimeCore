#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	 // Setting variables
	glm::vec3 lightPos[4] = { glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0) };
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

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
				(x - (num / 2)) * 2.0f,
				simplexNoise < 0.15f ? -3.2f : simplexNoise > 0.6f ? -1.2f : -3.0f,
				(y - (num / 2)) * 2.0f),
				Primitives::TYPE::Cube,
				simplexNoise > 0.2f ? grass : simplexNoise > 0.10f ? dirt : water, 0.5f, 0.65f, 50);
		}
	}

	// Testing
	Mesh* lightMesh = new Mesh();
	lightMesh->load("..\\Models\\teapot.obj");
	Shader* lightShader = new Shader("..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	Material* lightMaterial = new Material(lightShader, light);
	GameObject* lightOB[4] = { new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial)};

	for (int i = 0; i < 4; i++)
	{
		lightOB[i]->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));
	}

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;



		for (int i = 0; i < 4; i++)
		{
			lightPos[i] = glm::vec3(glm::cos(i % 2 ? -timer : timer) * (i * 6), 1, glm::sin(i % 2 ? -timer : timer) * (i * 6));
			lightOB[i]->SetPos(lightPos[i]);
			lightOB[i]->Draw(app->projectionViewMat, app->GetCamera());
			for (int x = 0; x < num; x++)
			{
				for (int y = 0; y < num; y++)
				{
					ground[x][y]->GetMaterial()->pointLights[i].SetLightPosition(lightPos[i]);
				}
			}
		}

		for (int x = 0; x < num; x++)
		{
			for (int y = 0; y < num; y++)
			{
				ground[x][y]->GetMaterial()->SetDirectionalLightDirection(glm::vec3(cos(timer), -1.0f, -0.3f));
				ground[x][y]->Draw(app->projectionViewMat, app->GetCamera());
			}
		}

		app->Update();
	}

	for (int x = 0; x < 4; x++)
	{
		delete lightOB[x];
	}

	for (int x = 0; x < num; x++)
	{
		for (int y = 0; y < num; y++)
		{
			delete ground[x][y];
		}
	}

	delete lightMaterial;
	delete lightMesh;
	delete grass;
	delete water;
	delete dirt;
	delete light;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}