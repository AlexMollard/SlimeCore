#pragma once
#include "PhysicsObject.h"
class RigidBody : public PhysicsObject
{
public:
	std::string name = "";

	glm::vec3 GetPos() { return position; };
	glm::vec3 GetVelocity() { return velocity; };
	glm::vec3 GetAcceleration() { return acceleration; };

	void SetPos(glm::vec3 newPos) { position = newPos; };
	void SetVelocity(glm::vec3 newVel) { velocity = newVel; };
	void AddVelocity(glm::vec3 newVel) { velocity += newVel; };
	void SetAcceleration(glm::vec3 newAcc) { acceleration = newAcc; };
	void fixedUpdate(glm::vec3 gravity, float timeStep);
	void Update(float deltaTime);
	bool GetKinematic() { return isKinematic; };
	void SetKinematic(bool value) { isKinematic = value; };
	void SetBoundingBox(glm::vec3 bLeft, glm::vec3 tRight);
	float GetMass() { return mass; };
	void SetMass(float newMass) { mass = newMass; };
	void ApplyForceToActor(RigidBody* obj, glm::vec3 force);
	void ApplyForce(glm::vec3 force);
	glm::vec3 GetBoundingBottomLeft() { return bottomLeft; };
	glm::vec3 GetBoundingTopRight() { return topRight; };
	glm::vec2 size = glm::vec2(1, 1);
protected:
	bool isKinematic = false;
	glm::vec3 position = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);
	glm::vec3 acceleration = glm::vec3(0);
	float mass = 1.0f;

	// Bounding box (For collision)
	glm::vec3 bottomLeft;
	glm::vec3 topRight;
};
