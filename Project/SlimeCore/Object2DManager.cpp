#include "Object2DManager.h"

Object2DManager::Object2DManager(TextureManager* textureManager)
{
	texManager = textureManager;
	TwoDShader = new Shader("TwoDShader", "..\\Shaders\\2DVertex.shader", "..\\Shaders\\2DFragment.shader");
	defaultWhite = texManager->Get(0, TEXTURETYPE::Albedo);
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
		TwoDShader->setVec3("position", objects[i]->position);
		
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

GameObject2D* Object2DManager::CreateBox(glm::vec3 Position, float xWidth, float yWidth)
{
	objects.push_back(new GameObject2D());
	GameObject2D* currentObject = objects.back();
	currentObject->tex = defaultWhite;
	currentObject->size = glm::vec2(xWidth, yWidth);


	currentObject->twoMesh.vertices.push_back(glm::vec3(-1.0f * xWidth, 1.0f * yWidth, 0.0f));	// Back-Left	0
	currentObject->twoMesh.vertices.push_back(glm::vec3(1.0f * xWidth, 1.0f * yWidth, 0.0f));	// Back-Right	1
	currentObject->twoMesh.vertices.push_back(glm::vec3(-1.0f * xWidth, -1.0f * yWidth, 0.0f));	// Front-Left	2
	currentObject->twoMesh.vertices.push_back(glm::vec3(1.0f * xWidth, -1.0f * yWidth, 0.0f));	//Front-Right	3

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
	currentObject->SetPos(Position);
	CreateMesh(currentObject);
	return currentObject;
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
