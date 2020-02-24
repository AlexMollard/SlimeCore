#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	ShaderManager* shaderManager = new ShaderManager();
	MaterialManager* materialManager = new MaterialManager();
	TextureManager* textureManager = new TextureManager();
	ObjectManager* objectManager = new ObjectManager(materialManager, shaderManager, textureManager, app->projectionViewMat);

	shaderManager->Create("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	shaderManager->Create("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	shaderManager->Create("skyBoxShader", "..\\Shaders\\SkyBoxVertex.shader", "..\\Shaders\\SkyBoxFragment.shader");

	textureManager->Create("Grass Texture", "..\\Images\\grass.png");
	textureManager->Create("Light Texture", "..\\Images\\light.png");

	//Skybox
	std::vector<std::string> faces
	{
		"..\\Images\\SkyBox\\skyrender0001.bmp",
		"..\\Images\\SkyBox\\skyrender0002.bmp",
		"..\\Images\\SkyBox\\skyrender0003.bmp",
		"..\\Images\\SkyBox\\skyrender0004.bmp",
		"..\\Images\\SkyBox\\skyrender0005.bmp",
		"..\\Images\\SkyBox\\skyrender0006.bmp"
	};
	textureManager->CreateSkyBox(faces);


	materialManager->Create("grassMat", textureManager->Get(0));
	materialManager->Create("lightMat", textureManager->Get(1));
	materialManager->Create("skyBoxMat", textureManager->Get(2));

	// Setting variables
	glm::vec3 lightPos[4] = { glm::vec3(0, 2, 0),glm::vec3(0, 2, 0),glm::vec3(0, 2, 0),glm::vec3(0, 2, 0) };
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;
	int gridSize = 5;

	Mesh* cube = new Mesh();
	cube->create(Primitives::Cube);

	Mesh* skyBox = new Mesh();
	skyBox->create(Primitives::SkyBox);

	std::vector<GameObject*> gm;
	for (int x = 0; x < gridSize; x++)
	{
		for (int y = 0; y < gridSize; y++)
		{
			gm.push_back(new GameObject("Green Cube: " + std::to_string(x) + ", " + std::to_string(y), cube, materialManager->Get(0), shaderManager->Get(0)));
			gm.back()->SetPos(glm::vec3((x * 2) - gridSize, -5, (y * 2) - gridSize));
		}
	}

	objectManager->AddArray(gm);

	// Testing
	GameObject* lightOB[4] = 
	{ 
		new GameObject("Light 0", cube, materialManager->Get(1), shaderManager->Get(1)),
		new GameObject("Light 1", cube, materialManager->Get(1), shaderManager->Get(1)),
		new GameObject("Light 2", cube, materialManager->Get(1), shaderManager->Get(1)),
		new GameObject("Light 3", cube, materialManager->Get(1), shaderManager->Get(1))
	};
	objectManager->AddArray(lightOB,4);

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

	objectManager->Create("SkyBox", skyBox, 2, 2);

	objectManager->DebugAll();

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
			objectManager->Create("New Object: " + std::to_string(currentCubeIndex),cube, 0, 0, glm::vec3(0, currentCubeIndex, 0));
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
	delete skyBox;
	delete shaderManager;
	delete materialManager;
	delete textureManager;
	delete objectManager;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}