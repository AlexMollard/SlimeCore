#include "FlyCamera.h"

FlyCamera::FlyCamera(glm::vec3 up)
{
	this->up = up;
}

void FlyCamera::Update(float deltaTime)
{
}

void FlyCamera::SetSpeed(float speed)
{
	this->speed = speed;
}
