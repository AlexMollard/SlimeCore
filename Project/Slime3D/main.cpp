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
	int gridSize = 5;

	Mesh* cube = new Mesh();
	cube->create(Primitives::Cube);

	std::vector<GameObject*> gm;
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			gm.push_back(new GameObject("Green Cube: " + std::to_string(x) + ", " + std::to_string(y), cube, materialManager->GetMaterialByIndex(0), shaderManager->GetShaderByIndex(0)));
			gm.back()->SetPos(glm::vec3((x * 2) - gridSize, 0, (y * 2) - gridSize));
		}
	}

	objectManager->AddGameObjectArray(gm);

	// Testing
	GameObject* lightOB[4] = 
	{ 
		new GameObject("Light 0", cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject("Light 1", cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject("Light 2", cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1)),
		new GameObject("Light 3", cube, materialManager->GetMaterialByIndex(1), shaderManager->GetShaderByIndex(1))
	};
	objectManager->AddGameObjectArray(lightOB,4);

	for (int i = 0; i < 4; i++)
	{
		lightOB[i]->SetScale(glm::vec3(0.25f, 0.25f, 0.25f));
	}

	int currentCubeIndex = 0;
	GameObject* currentGameObject = nullptr;
	glm::vec3 currentPOS = glm::vec3(0,2,0);

	std::vector<const char*> names;
	int currentName = 0;
	objectManager->SetNamesVector();
	names = objectManager->GetNameVector();

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

		// feed inputs to dear imgui, start new frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Start of gui window
		ImGui::Begin("Create Cube");

		if (ImGui::Button("Create"))
		{
			objectManager->CreateGameObject("New Object: " + std::to_string(currentCubeIndex),cube, 0, 0, glm::vec3(0, currentCubeIndex, 0));
			currentGameObject = objectManager->objects.back();
			currentCubeIndex++;
			objectManager->SetNamesVector();
			names = objectManager->GetNameVector();
		}

		ImGui::SliderFloat("X: ", &currentPOS.x, -100.0f, 100.0f);
		ImGui::SliderFloat("Y: ", &currentPOS.y, -100.0f, 100.0f);
		ImGui::SliderFloat("Z: ", &currentPOS.z, -100.0f, 100.0f);

		if (currentGameObject != nullptr)
			currentGameObject->SetPos(currentPOS);

		ImGui::ListBox("Objects", &currentName, names.data(), names.size());

		// End of gui window
		ImGui::End();

		// Render dear imgui into screen
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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