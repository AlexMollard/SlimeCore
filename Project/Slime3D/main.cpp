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
	ObjectManager* objectManager = new ObjectManager(materialManager, shaderManager, textureManager, app->projectionViewMat, &app->GetCamera()->Position);
	DebugGUI* debugGui = new DebugGUI(objectManager);

	// Setting variables
	float& deltaTime = *app->GetDeltaPointer();
	float timer = 0.0f;

	//Skybox
	shaderManager->Create("skyBoxShader", "..\\Shaders\\SkyBoxVertex.shader", "..\\Shaders\\SkyBoxFragment.shader");
	shaderManager->Create("defaultShader", "..\\Shaders\\Vertex.shader", "..\\Shaders\\Fragment.shader");
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
	textureManager->Create("Grass Texture", "..\\Images\\grass.png");
	materialManager->Create("skyBoxMat", textureManager->Get(0));
	materialManager->Create("grassMat", textureManager->Get(1));


	Mesh* cube = new Mesh();
	cube->create(Primitives::Cube);
	Mesh* skybox = new Mesh();
	skybox->create(Primitives::SkyBox);

	objectManager->Create("SkyBox", skybox, 0, 0);
	objectManager->Create("Block", cube, 1, 1);

	objectManager->DebugAll();
	debugGui->FirstFrame();
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;
		
		objectManager->objects[0]->SetPos(app->GetCamera()->Position);
		objectManager->Draw();
		debugGui->Render();
		app->Update();
	}

	delete skybox;
	delete cube;
	delete shaderManager;
	delete materialManager;
	delete textureManager;
	delete objectManager;
	delete debugGui;
	delete app;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}