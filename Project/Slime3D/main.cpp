#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	// Uncomment to enable line drawing
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	 // Setting variables
	glm::vec3 lightPos[4] = { glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0) };
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;
	const int mapSize = 10; 

	// Generating textures
	Texture* grass = new Texture("..\\Images\\grass.png");
	Texture* dirt  = new Texture("..\\Images\\dirt.png");
	Texture* water = new Texture("..\\Images\\water.png");
	Texture* light = new Texture("..\\Images\\light.png");

#pragma region Creating terrain
	// Ground Blocks
	GameObject* ground[mapSize][mapSize];
	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			float simplexNoise = glm::perlin(glm::vec2(x / 4.9f, y / 4.9f));
			ground[x][y] = new GameObject(glm::vec3(
				(x - (mapSize / 2)) * 2.0f ,
				simplexNoise < 0.15f ? -3.2f : simplexNoise > 0.6f ? -1.2f : -3.0f,
				(y - (mapSize / 2)) * 2.0f ),
				Primitives::TYPE::Cube,
				simplexNoise > 0.2f ? grass : simplexNoise > 0.10f ? dirt : water, 0.5f,0.65f,50);

			//Setting light Properties
			ground[x][y]->GetMaterial()->SetDirectionalLightAttributes();

			for (int i = 0; i < 4; i++)
			{
				ground[x][y]->GetMaterial()->pointLights[i].SetLightAttributes();
			}
		}
	}
#pragma endregion

	// Testing
	Mesh* testMesh = new Mesh();
	testMesh->create(Primitives::TYPE::Cube);

	// Setting up light object
	Shader* lightShader = new Shader("..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	Material* lightMaterial = new Material(lightShader, light);

	GameObject* lightOB[4] = { new GameObject(testMesh, lightMaterial), new GameObject(testMesh, lightMaterial), new GameObject(testMesh, lightMaterial), new GameObject(testMesh, lightMaterial)};

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
			lightPos[i] = glm::vec3(glm::cos(timer) * (i * 4), 1, glm::sin(timer) * (i * 4));
			lightOB[i]->SetPos(lightPos[i]);
			lightOB[i]->Draw(app->projectionViewMat, app->GetCamera());
		}

		for (int x = 0; x < mapSize; x++)
		{
			for (int y = 0; y < mapSize; y++)
			{
				for (int i = 0; i < 4; i++)
				{
					ground[x][y]->GetMaterial()->pointLights[i].SetLightPosition(lightPos[i]);
				}
				ground[x][y]->Draw(app->projectionViewMat, app->GetCamera());
			}
		}

		app->Update();
	}

	delete lightOB; 
	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			delete ground[x][y];
		}
	}
	delete grass;
	delete dirt;
	delete water;
	//delete light;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}