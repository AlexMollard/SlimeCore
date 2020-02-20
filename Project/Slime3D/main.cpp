#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	ShaderManager* shaderManager = new ShaderManager();
	MaterialManager* materialManager = new MaterialManager();
	ObjectManager* objectManager = new ObjectManager(materialManager,shaderManager, app->projectionViewMat);

	shaderManager->CreateShader("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	shaderManager->CreateShader("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");

	materialManager->CreateMaterial("grassMat", new Texture("..\\Images\\grass.png"));
	materialManager->CreateMaterial("lightMat", new Texture("..\\Images\\light.png"));

	printf("\n");
	shaderManager->DebugManager();
	materialManager->DebugManager();

	// Setting variables
	glm::vec3 lightPos[4] = { glm::vec3(0, 2, 0),glm::vec3(0, 2, 0),glm::vec3(0, 2, 0),glm::vec3(0, 2, 0) };
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;
	int gridSize = 50;

	Mesh* cube = new Mesh();
	cube->create(Primitives::Cube);

	std::vector<GameObject*> gm;
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			gm.push_back(new GameObject(cube, materialManager->GetMaterialByIndex(0), shaderManager->GetShaderByIndex(0)));
			gm.back()->SetPos(glm::vec3((x * 2) - gridSize, 0, (y * 2) - gridSize));
		}
	}

	objectManager->AddGameObjectArray(gm);

	// Testing
	GameObject* lightOB[4] = 
	{ 
		new GameObject(cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject(cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject(cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject(cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1))
	};
	objectManager->AddGameObjectArray(lightOB,4);

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
			lightPos[i] = glm::vec3(glm::cos(i % 2 ? -timer : timer) * (i * 6), 2, glm::sin(i % 2 ? -timer : timer) * (i * 6));
			lightOB[i]->SetPos(lightPos[i]);

			for (int x = 0; x < gm.size(); x++)
				gm[x]->GetMaterial()->pointLights[i].SetLightPosition(lightPos[i]);
		}

		objectManager->Draw();

		app->Update();
	}

	delete cube;
	delete shaderManager;
	delete materialManager;
	delete objectManager;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}