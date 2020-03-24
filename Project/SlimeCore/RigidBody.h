#pragma once
#include "PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	glm::vec3 GetPos() { return position; };
	glm::vec3 GetVelocity() { return velocity; };
	glm::vec3 GetAcceleration() { return acceleration; };

	void SetPos(glm::vec3 newPos) { position = newPos; };
	void SetVelocity(glm::vec3 newVel) { velocity = newVel; };
	void SetAcceleration(glm::vec3 newAcc) { acceleration = newAcc; };

	void Update(float deltaTime);

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

