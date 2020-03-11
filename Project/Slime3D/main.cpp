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
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Albedo));
	materialManager->Create("defaultMaterial", textureManager->Get(1, TEXTURETYPE::Albedo), textureManager->Get(1, TEXTURETYPE::Specular), textureManager->Get(1, TEXTURETYPE::Normal), textureManager->Get(1, TEXTURETYPE::Ambient), textureManager->Get(1, TEXTURETYPE::Rough), textureManager->Get(1, TEXTURETYPE::Displacement));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Albedo));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", "..\\Models\\cube.obj");
	meshManager->Create("Plane", Primitives::Plane);
	meshManager->Create("Cylinder", Primitives::Cylinder);
	
	// Load Stan
	meshManager->Create("sphere", "..\\Models\\sphere.obj");
	meshManager->Create("girl", "..\\Models\\girl\\tiphaine.obj");
	meshManager->Create("stormtrooper", "..\\Models\\stormtrooper\\0.obj");

	// Objects
	GameObject* skyBox = objectManager->Create("SkyBox", 1, 1, 1);
	objectManager->Create("Block", 2, 2, 3);
	objectManager->Get("Block")->SetPos(glm::vec3(0, -0.25f, 0));

	objectManager->CreatePointLight("Light", glm::vec3(2,0,0));

	debugGui->FirstFrame();

	GameObject* lightOBJ = objectManager->Get("Light");

	objectManager->DebugAll();
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += deltaTime;
		
		skyBox->SetSkyBoxPos(&app->GetCamera()->Position);
		lightOBJ->SetPos(glm::vec3(1,0,glm::cos(timer) / 2));
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