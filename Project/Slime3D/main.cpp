#include "Application.h"
#include "Game3D.h"

int main()
{
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

	// Creating Game3D
	Game3D* game = new Game3D(app->GetCamera(), objectManager, &deltaTime);

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		// Game Update
		game->Update();

		// Draw objects/Meshes
		objectManager->Draw(true);

		// Draw Gui
		debugGui->Render(deltaTime);

		// Update callbacks ect.
		app->Update();
	}

	// Delete pointers
	delete objectManager; // also deletes all other managers
	delete debugGui;
	delete app;
	delete game;

	// Destroy openGL instance
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}