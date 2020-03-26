#pragma once
#include "RigidBody.h"
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene() {};
	void addActor(RigidBody* actor);
	void addActor(std::vector<RigidBody*> actors);
	void addActor(RigidBody** actors, int amount);
	void removeActor(RigidBody* actor);
	void update(float dt); 
	bool CheckCollision(RigidBody& one, RigidBody& two);
	glm::vec3 GetOverLap(RigidBody& one, RigidBody& two);
	void setGravity(const glm::vec3 gravity) { this->gravity = gravity; }
	glm::vec3 getGravity() const { return gravity; }
	void setTimeStep(const float timeStep) { this->timeStep = timeStep; }
	float getTimeStep() const { return timeStep; }
protected:
	glm::vec3 gravity;
	float timeStep = 0.01f;
	std::vector<RigidBody*> actors;
};