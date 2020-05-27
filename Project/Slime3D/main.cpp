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
	DebugGUI* debugGui = new DebugGUI(objectManager, meshManager, materialManager, textureManager, shaderManager);

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();

	// Objects
	GameObject* skyBox = objectManager->Create("SkyBox", 1, 1, 1);
	objectManager->Create("Block", Primitives::TYPE::Cube, 2, 3);

	// Lights
	objectManager->CreatePointLight("PointLight", glm::vec3(1, 2, 1));

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		// Move skybox with camera
		skyBox->SetSkyBoxPos(&app->GetCamera()->Position);

		// Draw objects/Meshes
		objectManager->Draw(true);

		// Draw Gui
		debugGui->Render(deltaTime);

		// Update callbacks ect.
		app->Update();
	}

	// Delete pointers
	delete objectManager;
	delete debugGui;
	delete app;

	// Destroy openGL instance
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}