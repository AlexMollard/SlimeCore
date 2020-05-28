#include "RigidBody.h"

void RigidBody::Update(float deltaTime)
{
}

void RigidBody::SetBoundingBox(glm::vec3 bLeft, glm::vec3 tRight)
{
	bottomLeft = bLeft;
	topRight = tRight;
}

void RigidBody::ApplyForceToActor(RigidBody* obj, glm::vec3 force)
{
	obj->ApplyForce(-force);
	this->ApplyForce(force);
}

void RigidBody::ApplyForce(glm::vec3 force)
{
	velocity += force / mass;
}

void RigidBody::fixedUpdate(glm::vec3 gravity, float timeStep)
{
	//velocity += gravity * timeStep;
	position += velocity * timeStep;
}