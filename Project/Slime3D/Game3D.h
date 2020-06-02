#pragma once
#include "Camera.h"
#include "ObjectManager.h"

class Game3D
{
public:
	Game3D(Camera* cam, ObjectManager* objManager, float* deltaTime);
	~Game3D();

	void Init();

	void Update();

private:
	Camera* cam = nullptr;
	ObjectManager* objManager = nullptr;
	float* deltaTime = nullptr;

};

