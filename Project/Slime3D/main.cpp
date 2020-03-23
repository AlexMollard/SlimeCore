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
	Object2DManager* object2DManager = new Object2DManager(textureManager);
	
	// Creating debugging GUI
	DebugGUI* debugGui = new DebugGUI(objectManager, meshManager,materialManager,textureManager,shaderManager);

	textureManager->ImportAllTextures();

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

	GameObject2D* square = object2DManager->CreateBox();
	GameObject2D* testSquare = object2DManager->CreateBox(glm::vec3(4, 0, 0.1f), 2, 2);
	GameObject2D* testSquareTwo = object2DManager->CreateBox(glm::vec3(-3, 0, 0.2f), 0.5f, 0.5f);
	testSquareTwo->color = glm::vec3(0,1,0);
	testSquare->SetTexture(textureManager->Get("grass.png", TEXTURETYPE::Albedo));
	debugGui->FirstFrame();
	
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{	
		timer += deltaTime;
		square->Rotate(5 * deltaTime);

		// Draw 2D objects
		object2DManager->Draw();

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
	delete object2DManager;
	delete debugGui;
	delete app;

	// Destroy openGL instance
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}