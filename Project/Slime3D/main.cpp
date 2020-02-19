#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	ShaderManager* shaderManager = new ShaderManager();
	MaterialManager* materialManager = new MaterialManager();

	Texture* grass = new Texture("..\\Images\\grass.png");
	Texture* dirt = new Texture("..\\Images\\dirt.png");
	Texture* water = new Texture("..\\Images\\water.png");
	Texture* light = new Texture("..\\Images\\light.png");

	shaderManager->CreateShader("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	shaderManager->CreateShader("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");

	materialManager->CreateMaterial("grassMat", shaderManager->GetShaderByName(false, "defaultShader"), grass);
	materialManager->CreateMaterial("lightMat", shaderManager->GetShaderByIndex(1), light);

	printf("\n");
	shaderManager->DebugManager();
	materialManager->DebugManager();

	// Setting variables
	glm::vec3 lightPos[4] = { glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0),glm::vec3(0, 1, 0) };
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

	Mesh* cube = new Mesh();
	cube->create(Primitives::Cube);

	GameObject* gm = new GameObject(cube, materialManager->GetMaterialByIndex(0), shaderManager->GetShaderByIndex(0));

	// Testing
	Mesh* lightMesh = new Mesh();
	lightMesh->load("..\\Models\\teapot.obj");
	GameObject* lightOB[4] = { new GameObject(lightMesh, materialManager->GetMaterialByIndex(1)), new GameObject(lightMesh, materialManager->GetMaterialByIndex(1)), new GameObject(lightMesh, materialManager->GetMaterialByIndex(1)), new GameObject(lightMesh, materialManager->GetMaterialByIndex(1)) };

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
			gm->GetMaterial()->pointLights[i].SetLightPosition(lightPos[i]);

		}

		gm->GetMaterial()->SetDirectionalLightDirection(glm::vec3(cos(timer), -1.0f, -0.3f));
		gm->Draw(app->projectionViewMat, app->GetCamera());

		app->Update();
	}

	for (int x = 0; x < 4; x++)
	{
		delete lightOB[x];
	}
	delete cube;
	delete shaderManager;
	delete materialManager;
	delete gm;
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