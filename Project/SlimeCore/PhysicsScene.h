#pragma once
#include "PhysicsObject.h"
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();
	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float dt); 
	void updateGizmos();
	void setGravity(const glm::vec2 gravity) { this->gravity = gravity; }
	glm::vec2 getGravity() const { return gravity; }
	void setTimeStep(const float timeStep) { this->timeStep = timeStep; }
	float getTimeStep() const { return timeStep; }
protected:
	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
};