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
	shaderManager->Create("pbrShader", "..\\Shaders\\PbrVertex.shader", "..\\Shaders\\PbrFragment.shader");
	shaderManager->Create("lightShader", "..\\Shaders\\litVertex.shader", "..\\Shaders\\litFragment.shader");
	
	// Textures
	textureManager->CreateSkyBox("..\\Images\\SkyBox\\");
	textureManager->ImportAllTextures();

	// Materials
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Diffuse));
	materialManager->Create("defaultMaterial", textureManager->Get(1, TEXTURETYPE::Diffuse), textureManager->Get(1, TEXTURETYPE::Specular), textureManager->Get(1, TEXTURETYPE::Normal), textureManager->Get(1, TEXTURETYPE::Ambient), textureManager->Get(1, TEXTURETYPE::Rough));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Diffuse));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", Primitives::Cube);
	meshManager->Create("Plane", Primitives::Plane);
	meshManager->Create("Cylinder", Primitives::Cylinder);
	
	// Load Stan
	//meshManager->Create("stan", "..\\Models\\stan.obj");
	

	// Objects
	objectManager->Create("SkyBox", 1, 1, 1);
	objectManager->Create("Block", 2, 2, 3);
	objectManager->Get("Block")->SetDescription("This object is the default cube on startup.");

	objectManager->CreatePointLight("Light", glm::vec3(2,0,0));

	debugGui->FirstFrame();

	objectManager->DebugAll();
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;
		
		objectManager->Get(0)->SetSkyBoxPos(&app->GetCamera()->Position);

		// Draw Objects
		objectManager->Draw();

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