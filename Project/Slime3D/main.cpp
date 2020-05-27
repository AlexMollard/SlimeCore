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
<<<<<<< HEAD
	Object2DManager* object2DManager = new Object2DManager(textureManager);
	PhysicsScene* pScene = new PhysicsScene();
=======
>>>>>>> idk

	// Creating debugging GUI
	DebugGUI* debugGui = new DebugGUI(objectManager, meshManager, materialManager, textureManager, shaderManager);

	textureManager->ImportAllTextures();

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();
<<<<<<< HEAD
	float timer = 0.0f;

	GameObject2D* platform = object2DManager->CreateBox(glm::vec3(0,-8,0),15.0f,0.5f);
	platform->color = glm::vec3(0.3f);
	platform->SetKinematic(true);
	platform->name = "Platform1";

	GameObject2D* platform2 = object2DManager->CreateBox(glm::vec3(0, 7, 0), 15.0f, 0.5f);
	platform2->color = glm::vec3(0.3f);
	platform2->SetKinematic(true);
	platform2->name = "Platform2";

	GameObject2D* platform3 = object2DManager->CreateBox(glm::vec3(14.5f, -0.5f, 0), 0.5f, 6.0f);
	platform3->color = glm::vec3(0.3f);
	platform3->SetKinematic(true);
	platform3->name = "Platform3";

	GameObject2D* platform4 = object2DManager->CreateBox(glm::vec3(-14.5f, -0.5f, 0), 0.5f, 6.0f);
	platform4->color = glm::vec3(0.3f);
	platform4->SetKinematic(true);
	platform4->name = "Platform4";

	int size = 4;
	
	for (float x = 0; x < size; x++)
	{
		for (float y = 0; y < size; y++)
		{
			GameObject2D* currentOBJ = object2DManager->CreateBox(glm::vec3(x - size/2, y - size/2, 0), 0.25f, 0.25f);
			currentOBJ->color = glm::vec3(glm::sin(x / size), glm::sin(y / size), 0.3f);
			currentOBJ->name = "Cube";
			currentOBJ->ApplyForce(((int)x % 2 == 0) ? glm::vec3(0.80f, 0.0f, 0.0f) : glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}

	std::vector<GameObject2D*> allObjects = object2DManager->GetAllObjects();
	
	for (int i = 0; i < allObjects.size(); i++)
	{
		pScene->addActor((RigidBody*)allObjects[i]);
	}

	debugGui->FirstFrame();
	
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{	
		timer += deltaTime;

		// Draw 2D objects
		object2DManager->Update(deltaTime);
		object2DManager->Draw();
		pScene->update(deltaTime);
=======

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
>>>>>>> idk

		// Draw Gui
		debugGui->Render(deltaTime);

		// Update callbacks ect.
		app->Update();
	}

	// Delete pointers
<<<<<<< HEAD
	delete shaderManager;
	delete meshManager;
	delete materialManager;
	delete pScene;
	delete textureManager;
=======
>>>>>>> idk
	delete objectManager;
	delete object2DManager;
	delete debugGui;
	delete app;

	// Destroy openGL instance
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}