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

	GameObject2D* platform = object2DManager->CreateBox(glm::vec3(0,-8,0),15.0f,0.5f);
	platform->color = glm::vec3(0.3f);

	int size = 5;
	for (float x = 0; x < size; x++)
	{
		for (float y = 0; y < size; y++)
		{
			GameObject2D* currentOBJ = object2DManager->CreateBox(glm::vec3(x - size/2, y - size/2, 0), 0.25f, 0.25f);
			currentOBJ->color = glm::vec3(glm::cos((x / 3.0f)), glm::cos((y / 3.0f)),0);
			currentOBJ->SetAcceleration(glm::vec3(x * 0.01f, -3.9f / 50, 0));
		}
	}

	debugGui->FirstFrame();
	
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{	
		timer += deltaTime;

		// Draw 2D objects
		object2DManager->Draw();
		object2DManager->Update(deltaTime);

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