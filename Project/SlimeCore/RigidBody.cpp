#include "RigidBody.h"

void RigidBody::Update(float deltaTime)
{
	position += velocity * deltaTime;
	velocity += acceleration * deltaTime;
}
