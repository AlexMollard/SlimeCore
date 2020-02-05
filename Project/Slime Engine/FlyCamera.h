#pragma once
#include "Camera.h"
class FlyCamera : public Camera
{
	float speed = 1.0f;
	glm::vec3 up = glm::vec3(0);

public:
	FlyCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void Update(float deltaTime);
	void SetSpeed(float speed);
};

