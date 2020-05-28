#include "Game3D.h"

Game3D::Game3D(Camera* cam, ObjectManager* objManager, float* deltaTime)
{
	this->cam = cam;
	this->objManager = objManager;
	this->deltaTime = deltaTime;

	// Objects
	objManager->Create("TestingCube", Primitives::TYPE::Cube, glm::vec3(2, 2, 2));
	objManager->Create("Block", Primitives::TYPE::Cube);

	// Lights
	objManager->CreatePointLight("TestingPointLight", glm::vec3(-1),glm::vec3(1,0,0));
	objManager->CreatePointLight("PointLight", glm::vec3(1, 2, 1));
}

Game3D::~Game3D()
{
}

void Game3D::Update()
{
	std::cout << deltaTime[0] << std::endl;
}
