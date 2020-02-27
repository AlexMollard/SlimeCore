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
	
	//Diffuses
	textureManager->Create("Grass", "..\\Images\\Diffuse\\grass.png",TEXTURETYPE::Diffuse);
	textureManager->Create("Water", "..\\Images\\Diffuse\\water.png", TEXTURETYPE::Diffuse);
	textureManager->Create("Dirt", "..\\Images\\Diffuse\\dirt.png", TEXTURETYPE::Diffuse);
	textureManager->Create("White", "..\\Images\\Diffuse\\light.png", TEXTURETYPE::Diffuse);
	textureManager->Create("Slime", "..\\Images\\Diffuse\\missingTex.png", TEXTURETYPE::Diffuse);
	textureManager->Create("UV", "..\\Images\\Diffuse\\test.jpg", TEXTURETYPE::Diffuse);
	textureManager->Create("Rock", "..\\Images\\Diffuse\\Rock.jpg", TEXTURETYPE::Diffuse);
	textureManager->Create("Ice", "..\\Images\\Diffuse\\Ice.jpg", TEXTURETYPE::Diffuse);
	textureManager->Create("Bark", "..\\Images\\Diffuse\\Bark.jpg", TEXTURETYPE::Diffuse);

	//Specs
	textureManager->Create("Bark Spec", "..\\Images\\Specular\\Bark.png", TEXTURETYPE::Specular);
	textureManager->Create("Rock Spec", "..\\Images\\Specular\\Rock.png", TEXTURETYPE::Specular);
	textureManager->Create("Ice Spec", "..\\Images\\Specular\\Ice.png", TEXTURETYPE::Specular);

	//Normals
	textureManager->Create("Bark Norm", "..\\Images\\Normal\\Bark.jpg", TEXTURETYPE::Normal);
	textureManager->Create("Rock Norm", "..\\Images\\Normal\\Rock.jpg", TEXTURETYPE::Normal);
	textureManager->Create("Ice Norm", "..\\Images\\Normal\\Ice.jpg", TEXTURETYPE::Normal);
	textureManager->Create("Couch Norm", "..\\Images\\Normal\\Couch.jpg", TEXTURETYPE::Normal);
	textureManager->Create("Leather Norm", "..\\Images\\Normal\\Leather.png", TEXTURETYPE::Normal);
	textureManager->Create("Brick Norm", "..\\Images\\Normal\\Brick.jpg", TEXTURETYPE::Normal);
	textureManager->Create("Polygon Norm", "..\\Images\\Normal\\Polygon.jpg", TEXTURETYPE::Normal);

	//Ambients
	textureManager->Create("Bark Amb", "..\\Images\\Ambient\\Bark.jpg", TEXTURETYPE::Ambient);
	textureManager->Create("Rock Amb", "..\\Images\\Ambient\\Rock.jpg", TEXTURETYPE::Ambient);
	textureManager->Create("Ice Amb", "..\\Images\\Ambient\\Ice.jpg", TEXTURETYPE::Ambient);

	// Materials
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Diffuse));
	materialManager->Create("grassMat", textureManager->Get(0, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient));
	materialManager->Create("waterMat", textureManager->Get(1, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient));
	materialManager->Create("dirtMat", textureManager->Get(2, TEXTURETYPE::Diffuse), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", Primitives::Cube);
	meshManager->Create("Plane", Primitives::Plane);
	meshManager->Create("Cylinder", Primitives::Cylinder);

	// Objects
	objectManager->Create("SkyBox", 0, 0, 0);
	objectManager->Create("Block", 1, 2, 2);
	objectManager->Create("Ground", 2, 1, 2);
	objectManager->Get("Ground")->SetScale(glm::vec3(100,1,100));
	objectManager->Get("Ground")->SetPos(glm::vec3(0,-5,0));

	objectManager->DebugAll();
	debugGui->FirstFrame();
	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += 0.5f * deltaTime;
		
		// Set SkyBox on camera
		objectManager->objects[0]->SetPos(app->GetCamera()->Position);

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