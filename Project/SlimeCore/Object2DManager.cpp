#include "Object2DManager.h"

Object2DManager::Object2DManager(TextureManager* textureManager)
{
	texManager = textureManager;
	TwoDShader = new Shader("TwoDShader", "..\\Shaders\\2DVertex.shader", "..\\Shaders\\2DFragment.shader");
	defaultWhite = texManager->Get(0, TEXTURETYPE::Albedo);
	defaultCircleTexture = texManager->Create("CircleSprite", "..\\Images\\Sprites\\circle.png", TEXTURETYPE::Albedo);
}

Object2DManager::~Object2DManager()
{
	delete TwoDShader;
	TwoDShader = nullptr;
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
}

void Object2DManager::Draw()
{
	TwoDShader->Use();
	TwoDShader->setMat4("OrthoMatrix", orthoMatrix);

	for (int i = 0; i < objects.size(); i++)
	{
		TwoDShader->setMat4("Model", objects[i]->model);
		TwoDShader->setVec3("color", objects[i]->color);
		TwoDShader->setVec3("position", objects[i]->GetPos());
		
		//Texture Binding
		if (objects[i]->tex != nullptr && currentTexture != objects[i]->tex)
		{
			currentTexture = objects[i]->tex;
			TwoDShader->setInt("Texture", 0);
			glActiveTexture(GL_TEXTURE0);
			objects[i]->tex->Bind();
			objects[i]->Draw();
			continue;
		}

		objects[i]->Draw();
	}
}

void Object2DManager::Update(float deltaTime)
{
	for (int i = 0; i < objects.size(); i++)
	{
		//objects[i]->Update(deltaTime);
		objects[i]->UpdatePos();
	}
}

std::vector<GameObject2D*> Object2DManager::GetAllObjects()
{
	return objects;
}

GameObject2D* Object2DManager::CreateBox(glm::vec3 Position, float width, float height)
{
	objects.push_back(new GameObject2D());
	GameObject2D* currentObject = objects.back();
	currentObject->tex = defaultWhite;
	currentObject->size = glm::vec2(width, height);

	glm::vec3 topLeft = glm::vec3(-1.0f * width, 1.0f * height, 0.0f);
	glm::vec3 bottomLeft = glm::vec3(1.0f * width, 1.0f * height, 0.0f);
	glm::vec3 topRight = glm::vec3(-1.0f * width, -1.0f * height, 0.0f);
	glm::vec3 bottomRight = glm::vec3(1.0f * width, -1.0f * height, 0.0f);

	SetUpSpriteMesh(currentObject, topLeft, bottomLeft, topRight, bottomRight);
	currentObject->SetPos(Position);

	//Setting bounding box
	glm::vec3 bLeft;
	glm::vec3 tRight;
	
	bLeft = glm::vec3(-width / 2, -height / 2, 0);
	tRight = glm::vec3(width * 0.5f, height * 0.5f, 0);
	
	currentObject->SetBoundingBox(bLeft, tRight);

	return currentObject;
}

GameObject2D* Object2DManager::CreateLine(glm::vec3 startPosition, glm::vec3 endPosition, float width)
{
	objects.push_back(new GameObject2D());
	GameObject2D* currentObject = objects.back();
	currentObject->tex = defaultWhite;
	currentObject->size = glm::vec2(width, width);

	glm::vec3 topLeft = glm::vec3(startPosition.x, startPosition.y - (width / 2), startPosition.z);
	glm::vec3 bottomLeft = glm::vec3(startPosition.x, startPosition.y + (width / 2), startPosition.z);
	glm::vec3 topRight = glm::vec3(endPosition.x, endPosition.y - (width / 2), endPosition.z);
	glm::vec3 bottomRight = glm::vec3(endPosition.x, endPosition.y + (width / 2), endPosition.z);

	SetUpSpriteMesh(currentObject, topLeft, bottomLeft, topRight, bottomRight);

	return currentObject;
}

GameObject2D* Object2DManager::CreateCircle(glm::vec3 Position, float Diameter)
{
	objects.push_back(new GameObject2D());
	GameObject2D* currentObject = objects.back();
	currentObject->tex = defaultCircleTexture;
	currentObject->size = glm::vec2(Diameter, Diameter);

	glm::vec3 topLeft = glm::vec3(-1.0f * Diameter, 1.0f * Diameter, 0.0f);
	glm::vec3 bottomLeft = glm::vec3(1.0f * Diameter, 1.0f * Diameter, 0.0f);
	glm::vec3 topRight = glm::vec3(-1.0f * Diameter, -1.0f * Diameter, 0.0f);
	glm::vec3 bottomRight = glm::vec3(1.0f * Diameter, -1.0f * Diameter, 0.0f);

	SetUpSpriteMesh(currentObject, topLeft, bottomLeft, topRight, bottomRight);
	currentObject->SetPos(Position);
	return currentObject;
}

void Object2DManager::SetUpSpriteMesh(GameObject2D* currentObject, glm::vec3 topLeft, glm::vec3 bottomLeft, glm::vec3 topRight, glm::vec3 bottomRight)
{
	currentObject->twoMesh.vertices.push_back(topLeft);	// Back-Left	0
	currentObject->twoMesh.vertices.push_back(bottomLeft);	// Back-Right	1
	currentObject->twoMesh.vertices.push_back(topRight);	// Front-Left	2
	currentObject->twoMesh.vertices.push_back(bottomRight); //Front-Right	3

	unsigned int planeIndices[] =
	{
		0, 2, 1,	// first triangle
		1, 2, 3		// second triangle
	};

	currentObject->twoMesh.uvs.push_back(glm::vec2(0, 1));
	currentObject->twoMesh.uvs.push_back(glm::vec2(1, 1));
	currentObject->twoMesh.uvs.push_back(glm::vec2(0, 0));
	currentObject->twoMesh.uvs.push_back(glm::vec2(1, 0));

	int length = sizeof(planeIndices) / sizeof(unsigned int);

	currentObject->twoMesh.indices = std::vector<unsigned int>(planeIndices, planeIndices + length);
	CreateMesh(currentObject);
}

void Object2DManager::CreateMesh(GameObject2D* currentObject)
{
	std::vector<float> newvertices;
	for (int i = 0; i < currentObject->twoMesh.vertices.size(); i++)
	{
		// Postitions
		newvertices.push_back(currentObject->twoMesh.vertices[i].x);
		newvertices.push_back(currentObject->twoMesh.vertices[i].y);
		newvertices.push_back(currentObject->twoMesh.vertices[i].z);

		// UVS
		if (currentObject->twoMesh.uvs.size() < 1)
		{
			newvertices.push_back(0.5);
			newvertices.push_back(0.5);

		}
		else
		{
			newvertices.push_back(currentObject->twoMesh.uvs[i].x);
			newvertices.push_back(currentObject->twoMesh.uvs[i].y);
		}
	}

	// generate buffers
	glGenBuffers(1, &currentObject->vbo);
	glGenBuffers(1, &currentObject->ibo);
	glGenVertexArrays(1, &currentObject->vao);
	// bind vertex array aka a mesh wrapper
	glBindVertexArray(currentObject->vao);

	// Fill vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, currentObject->vbo);
	glBufferData(GL_ARRAY_BUFFER, newvertices.size() * sizeof(float), newvertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentObject->ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, currentObject->twoMesh.indices.size() * sizeof(unsigned int), currentObject->twoMesh.indices.data(), GL_STATIC_DRAW);

	// Enable first element as position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Enable third element as UVS
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Unbind buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
