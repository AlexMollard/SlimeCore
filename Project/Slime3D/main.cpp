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
	DebugGUI* debugGui = new DebugGUI(objectManager, meshManager,materialManager,textureManager,shaderManager);

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

	// Shaders
	shaderManager->Create("skyBoxShader", "..\\Shaders\\SkyBoxVertex.shader", "..\\Shaders\\SkyBoxFragment.shader");
	shaderManager->Create("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
	Shader* pShader = shaderManager->Create("pbrShader", "..\\Shaders\\PbrVertex.shader", "..\\Shaders\\PbrFragment.shader");
	shaderManager->Create("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	Shader* debugShader = shaderManager->Create("debugShader", "..\\Shaders\\DebugVertex.shader", "..\\Shaders\\DebugFragment.shader");
	
	// Textures
	textureManager->CreateSkyBox("..\\Images\\SkyBox\\");
	textureManager->ImportAllTextures();

	// Materials
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Albedo));
	materialManager->Create("defaultMaterial", textureManager->Get("Planks.jpg", TEXTURETYPE::Albedo), textureManager->Get("Planks.jpg", TEXTURETYPE::Specular), textureManager->Get("Planks.jpg", TEXTURETYPE::Normal), textureManager->Get("Planks.jpg", TEXTURETYPE::Ambient), textureManager->Get("Planks.jpg", TEXTURETYPE::Rough), textureManager->Get(0, TEXTURETYPE::Displacement));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Albedo));
	materialManager->Create("debugMat", textureManager->Get(5, TEXTURETYPE::Albedo));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", "..\\Models\\cube.obj");
	meshManager->Create("Plane", Primitives::Plane);
	meshManager->Create("Cylinder", Primitives::Cylinder);
	
	// Load Objs
	meshManager->Create("sphere", "..\\Models\\sphere.obj");
	meshManager->Create("girl", "..\\Models\\girl\\tiphaine.obj");
	meshManager->Create("stormtrooper", "..\\Models\\stormtrooper\\0.obj");

	// Objects
	GameObject* skyBox = objectManager->Create("SkyBox", 1, 1, 1);
	objectManager->Create("Block", 2, 2, 3);
	objectManager->Get("Block")->SetPos(glm::vec3(0, -1, 0));
	objectManager->Get("Block")->SetScale(glm::vec3(5, 1, 5));

	// Create girl and set pos
	GameObject* Girl = objectManager->Create("Girl", 6, 1, 3);
	Girl->SetPos(glm::vec3(1, 0, 0));

	// Create stormTrooper and set pos
	GameObject* StormTrooper = objectManager->Create("StormTrooper", 7, 1, 3);
	StormTrooper->SetPos(glm::vec3(-1, 0, 0));

	// Setting moving lights up
	PointLight* movingLightOne = (PointLight*)objectManager->CreatePointLight("MovingLightOne", glm::vec3(2,2,0));
	PointLight* movingLightTwo = (PointLight*)objectManager->CreatePointLight("MovingLightTwo", glm::vec3(1,2,1));

	// Setting static lights up
	PointLight* stormTrooperLight = (PointLight*)objectManager->CreatePointLight("StormTrooperLight", glm::vec3(-1,2,1));
	stormTrooperLight->SetAlbedo(glm::vec3(1,0,0));
	PointLight* girlLight = (PointLight*)objectManager->CreatePointLight("GirlLight", glm::vec3(1,2,1));
	girlLight->SetAlbedo(glm::vec3(0,0,1));


	objectManager->DebugAll();
	debugGui->FirstFrame();
	
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += deltaTime;
		movingLightOne->SetAlbedo(glm::vec3(sin(timer), sin(timer + 1), sin(timer + 2)));
		movingLightTwo->SetAlbedo(glm::vec3(sin(timer + 3), sin(timer + 4), sin(timer + 5)));
		movingLightOne->SetPos(glm::vec3(sin(timer) * 3.0f, cos(timer) * 2.0f, cos(timer) * 3.0f));
		movingLightTwo->SetPos(glm::vec3(sin(timer + 3) * 3.0f, cos(timer + 3) * 2.0f, cos(timer + 3) * 3.0f));

		skyBox->SetSkyBoxPos(&app->GetCamera()->Position);

		objectManager->Draw(true);

		// Draw Gui
		debugGui->Render(deltaTime);

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