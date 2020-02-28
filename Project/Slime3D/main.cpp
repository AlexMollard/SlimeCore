#include "Application.h"

int main()
{
	// Check for Memory Leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Create Application
	Application* app = new Application(1280, 720, "Slime Core");
	GLFWwindow* window = glfwGetCurrentContext();

	// Create Managers
	ShaderManager* shaderManager = new ShaderManager();
	TextureManager* textureManager = new TextureManager();
	MaterialManager* materialManager = new MaterialManager(textureManager);
	MeshManager* meshManager = new MeshManager();
	ObjectManager* objectManager = new ObjectManager(meshManager, materialManager, shaderManager, textureManager, app->projectionViewMat, &app->GetCamera()->Position);
	
	// Creating debugging GUI
	DebugGUI* debugGui = new DebugGUI(objectManager, meshManager);

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

	// Shaders
	shaderManager->Create("skyBoxShader", "..\\Shaders\\SkyBoxVertex.shader", "..\\Shaders\\SkyBoxFragment.shader");
	shaderManager->Create("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	shaderManager->Create("pbrShader", "..\\Shaders\\PbrVertex.shader", "..\\Shaders\\PbrFragment.shader");
	shaderManager->Create("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	
	//Skybox
	std::vector<std::string> faces
	{
		"..\\Images\\SkyBox\\right.png",
		"..\\Images\\SkyBox\\left.png",
		"..\\Images\\SkyBox\\top.png",
		"..\\Images\\SkyBox\\bottom.png",
		"..\\Images\\SkyBox\\front.png",
		"..\\Images\\SkyBox\\back.png"
	};
	textureManager->CreateSkyBox(faces);
	
	textureManager->ImportAllTextures();

	// Materials
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Diffuse));
	materialManager->Create("grassMat", textureManager->Get(0, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient), textureManager->Get(0, TEXTURETYPE::Rough));
	materialManager->Create("waterMat", textureManager->Get(1, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient), textureManager->Get(0, TEXTURETYPE::Rough));
	materialManager->Create("dirtMat", textureManager->Get(2, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient), textureManager->Get(0, TEXTURETYPE::Rough));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Diffuse));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", Primitives::Cube);

	// Objects
	objectManager->Create("SkyBox", 0, 0, 0);
	objectManager->Create("Block", 1, 2, 2);

	GameObject* lights[4];

	lights[0] = objectManager->Create("Light1", 1, 4, 3, glm::vec3(3));
	lights[1] = objectManager->Create("Light2", 1, 4, 3, glm::vec3(3));
	lights[2] = objectManager->Create("Light3", 1, 4, 3, glm::vec3(3));
	lights[3] = objectManager->Create("Light4", 1, 4, 3, glm::vec3(3));

	for (int i = 0; i < 4; i++)
	{
		lights[i]->SetScale(glm::vec3(0.10f));
	}

	debugGui->FirstFrame();

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;
		
		// Set SkyBox on camera
		objectManager->objects[0]->SetPos(app->GetCamera()->Position);

		for (int i = 0; i < 4; i++)
		{
			lights[i]->SetPos(glm::vec3(glm::cos(timer) * (i * 2), 2, glm::sin(timer) * (i * 2)));
		}
		materialManager->SetSpotLightPos(lights[0]->GetPos(), lights[1]->GetPos(), lights[2]->GetPos(), lights[3]->GetPos());

		// Draw Objects
		objectManager->Draw();

		// Draw Gui
		debugGui->Render();

		// Update callbacks ect.
		app->Update();
	}

	// Delete pointers
	delete shaderManager;
	delete meshManager;
	delete materialManager;
	delete textureManager;
	delete objectManager;
	delete debugGui;
	delete app;

	// Destroy openGL instance
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}