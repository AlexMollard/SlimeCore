#pragma once
#include "Camera.h"
class FlyCamera : public Camera
{
	float speed = 1.0f;
	glm::vec3 up = glm::vec3(0);

public:
	FlyCamera(glm::vec3 up);

	void Update(float deltaTime);
	void SetSpeed(float speed);
};

