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

	// Generating textures
	Texture* grass = new Texture("..\\Images\\grass.png");
	Texture* light = new Texture("..\\Images\\light.png");

	// Testing
	Mesh* lightMesh = new Mesh();
	lightMesh->create(Primitives::TYPE::Cube);
	Shader* lightShader = new Shader("..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	Material* lightMaterial = new Material(lightShader, light);
	GameObject* lightOB[4] = { new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial), new GameObject(lightMesh, lightMaterial)};

	// Test Plane
	GameObject* plane = new GameObject(glm::vec3(0,-20,0),Primitives::TYPE::Cube,grass);
	plane->SetScale(glm::vec3(20, 20, 20));
	plane->GetMaterial()->SetDirectionalLightAttributes();
	
	for (int i = 0; i < 4; i++)
	{
		lightOB[i]->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));
	}

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;

		plane->GetMaterial()->SetDirectionalLightDirection(glm::vec3(cos(timer), -1.0f, -0.3f));

		for (int i = 0; i < 4; i++)
		{
			lightPos[i] = glm::vec3(glm::cos(i % 2 ? -timer : timer) * (i * 6), 1, glm::sin(i % 2 ? -timer : timer) * (i * 6));
			lightOB[i]->SetPos(lightPos[i]);
			lightOB[i]->Draw(app->projectionViewMat, app->GetCamera());

			plane->GetMaterial()->pointLights[i].lightPosition = lightPos[i];
			plane->Draw(app->projectionViewMat, app->GetCamera());
		}

		app->Update();
	}

	for (int x = 0; x < 4; x++)
	{
		delete lightOB[x];
	}

	delete plane;
	delete lightMaterial;
	delete lightMesh;
	delete grass;
	delete light;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}