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
	materialManager->Create("defaultMaterial", textureManager->Get(1, TEXTURETYPE::Albedo), textureManager->Get(1, TEXTURETYPE::Specular), textureManager->Get(1, TEXTURETYPE::Normal), textureManager->Get(1, TEXTURETYPE::Ambient), textureManager->Get(1, TEXTURETYPE::Rough), textureManager->Get(0, TEXTURETYPE::Displacement));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Albedo));
	materialManager->Create("debugMat", textureManager->Get(5, TEXTURETYPE::Albedo));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", "..\\Models\\cube.obj");
	Mesh* plane = meshManager->Create("Plane", Primitives::Plane);
	meshManager->Create("Cylinder", Primitives::Cylinder);
	
	// Load Objs
	//meshManager->Create("sphere", "..\\Models\\sphere.obj");
	//meshManager->Create("girl", "..\\Models\\girl\\tiphaine.obj");
	//meshManager->Create("stormtrooper", "..\\Models\\stormtrooper\\0.obj");

	// Objects
	GameObject* skyBox = objectManager->Create("SkyBox", 1, 1, 1);
	objectManager->Create("Block", 2, 2, 3);
	objectManager->Get("Block")->SetPos(glm::vec3(0, 0, 0));
	objectManager->Create("Block2", 2, 2, 3);
	objectManager->Get("Block2")->SetPos(glm::vec3(0, -1, 0));
	objectManager->Get("Block2")->SetScale(glm::vec3(5, 1, 5));

	GameObject* lightOBJ = objectManager->CreatePointLight("Light", glm::vec3(2,2,0));

	GameObject* debugObject = objectManager->Create("DeBugUI",3,4,5);
	debugObject->isDebugObject = true;
	objectManager->DebugAll();
	debugGui->FirstFrame();

	debugShader->Use();
	debugShader->setInt("Texture", 0);






	// framebuffer configuration
	// -------------------------
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	// create a color attachment texture
	unsigned int textureColorbuffer;
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, app->appWindowWidth, app->appWindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, app->appWindowWidth, app->appWindowHeight); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
	// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	debugObject->GetMaterial()->GetAlbedo()->SetID(textureColorbuffer);

	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += deltaTime;
		lightOBJ->SetPos(glm::vec3(sin(glfwGetTime()) * 3.0f, cos(glfwGetTime()) * 2.0f, cos(glfwGetTime()) * 3.0f));
		glm::vec3 lightPos = lightOBJ->GetPos();

		skyBox->SetSkyBoxPos(&app->GetCamera()->Position);


		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		objectManager->Draw(true);


		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		 

		debugObject->GetShader()->Use();
		glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
		glBindTexture(GL_TEXTURE_2D, debugObject->GetTexture(TEXTURETYPE::Albedo)->GetID());
		debugObject->Draw(&app->GetCamera()->GetProjectionViewMatrix());

		// Draw Quad
		//objectManager->Draw(false);

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