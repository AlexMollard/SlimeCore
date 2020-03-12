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
	
	// Textures
	textureManager->CreateSkyBox("..\\Images\\SkyBox\\");
	textureManager->ImportAllTextures();

	// Materials
	materialManager->Create("skyBoxMat", textureManager->Get(0, TEXTURETYPE::Albedo));
	materialManager->Create("defaultMaterial", textureManager->Get(0, TEXTURETYPE::Albedo), textureManager->Get(0, TEXTURETYPE::Specular), textureManager->Get(0, TEXTURETYPE::Normal), textureManager->Get(0, TEXTURETYPE::Ambient), textureManager->Get(0, TEXTURETYPE::Rough), textureManager->Get(0, TEXTURETYPE::Displacement));
	materialManager->Create("lightMat", textureManager->Get(3, TEXTURETYPE::Albedo));

	// Meshes
	meshManager->Create("SkyBox", Primitives::SkyBox);
	meshManager->Create("Cube", "..\\Models\\cube.obj");
	meshManager->Create("Plane", Primitives::Plane);
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

	objectManager->CreatePointLight("Light", glm::vec3(2,0,0));

	debugGui->FirstFrame();

	GameObject* lightOBJ = objectManager->Get("Light");

	objectManager->DebugAll();

	Shader* depthShader = shaderManager->Create("simpleDepthShader","..\\Shaders\\PointShadowDepthVertex.shader", "..\\Shaders\\PointShadowDepthFragment.shader", "..\\Shaders\\PointShadowDepthGeometry.shader");
	
	// configure depth map FBO
	// -----------------------
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	
	// create depth cubemap texture
	unsigned int depthCubemap;
	glGenTextures(1, &depthCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	// Main engine loop
	while (glfwWindowShouldClose(window) == false)
	{
		timer += deltaTime;
		skyBox->SetSkyBoxPos(&app->GetCamera()->Position);


		// 0. create depth cubemap transformation matrices
	   // -----------------------------------------------
		float near_plane = 1.0f;
		float far_plane = 25.0f;
		glm::vec3 lightPos = lightOBJ->GetPos();
		glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
		std::vector<glm::mat4> shadowTransforms;
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));


		// 1. render scene to depth cubemap
		// --------------------------------
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		depthShader->Use();
		for (unsigned int i = 0; i < 6; ++i)
			depthShader->setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
		depthShader->setVec3("lightPos", lightPos);
		objectManager->Draw(depthShader);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		// 2. render scene as normal
		// --------------------------------
		// Draw Objects
		glViewport(0, 0, app->appWindowWidth, app->appWindowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		objectManager->Draw(nullptr, &depthCubemap);

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