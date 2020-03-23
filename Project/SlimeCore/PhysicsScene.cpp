#include "PhysicsScene.h"


PhysicsScene::PhysicsScene() : timeStep(0.01f), gravity(glm::vec2(0, 0))
{
}

void PhysicsScene::update(float dt) {
	
	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	while(accumulatedTime >= timeStep)
	{
		for(auto pActor : actors)
		{
			pActor->fixedUpdate(gravity, timeStep);
		}
		accumulatedTime -= timeStep;
	}
}

void PhysicsScene::updateGizmos()
{
	for(auto pActor : actors) 
	{
		pActor->makeGizmo();
	}
}