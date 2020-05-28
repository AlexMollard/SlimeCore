#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "GameObject2D.h"
PhysicsScene::PhysicsScene() : timeStep(0.01f), gravity(glm::vec3(0, -0.32f, 0))
{
}

void PhysicsScene::addActor(RigidBody* actor)
{
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i] == actor)
		{
			std::cout << "Actor already exist in physics scene" << std::endl;
			break;
		}
	}
	actors.push_back(actor);
}

void PhysicsScene::addActor(std::vector<RigidBody*> actors)
{
	addActor(actors.data(), actors.size());
}

void PhysicsScene::addActor(RigidBody** actors, int amount)
{
	for (int i = 0; i < amount; i++)
		this->actors.push_back(actors[i]);
}

void PhysicsScene::removeActor(RigidBody* actor)
{
	auto location = std::find(actors.begin(), actors.end(), actor);
	actors.erase(location);
}

void PhysicsScene::update(float dt) {
	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	while (accumulatedTime >= timeStep)
	{
		for (auto pActor : actors)
		{
			if (!pActor->GetKinematic())
				pActor->fixedUpdate(gravity, timeStep);
		}
		accumulatedTime -= timeStep;
	}

	static std::vector<RigidBody*> dirty;

	for (auto object : actors)
	{
		for (auto other : actors)
		{
			if (object == other)
				continue;

			if (std::find(dirty.begin(), dirty.end(), object) != dirty.end() && std::find(dirty.begin(), dirty.end(), other) != dirty.end())
			{
				continue;
			}

			if (CheckCollision(*object, *other))
			{
				glm::vec3 overLap = GetOverLap(*object, *other);
				if (overLap.x != 0 || overLap.y != 0)
				{
					if (other->GetKinematic())
					{
						object->SetPos(object->GetPos() + overLap * 0.25f);
					}
					else if (object->GetKinematic())
					{
						other->SetPos(other->GetPos() - overLap * 0.25f);
					}
					else
					{
						other->SetPos(other->GetPos() - overLap * 0.25f);
						object->SetPos(object->GetPos() + overLap * 0.25f);
					}
				}

				object->ApplyForceToActor(other, object->GetVelocity() * object->GetMass());

				std::cout << object->name << " Collided with: " << other->name << std::endl;

				dirty.push_back(object);
				dirty.push_back(other);
			}
		}
	}
	dirty.clear();
}

bool PhysicsScene::CheckCollision(RigidBody& one, RigidBody& two)
{
	bool collisionX = one.GetPos().x + one.size.x < two.GetPos().x - two.size.x ||
		one.GetPos().x - one.size.x > two.GetPos().x + two.size.x;

	bool collisionY = one.GetPos().y + one.size.y < two.GetPos().y - two.size.y ||
		one.GetPos().y - 0.5 * one.size.y > two.GetPos().y + two.size.y;

	return !(collisionX || collisionY);
}

glm::vec3 PhysicsScene::GetOverLap(RigidBody& one, RigidBody& two)
{
	glm::vec3 overlap = { 0,0,0 };
	float overlap_size = 999999999999.0f;
	bool hasChanged = false;

	float a = one.GetPos().x + one.size.x - two.GetPos().x - two.size.x;
	if (abs(a) < overlap_size)
	{
		overlap_size = a;
		overlap.x = a;
		hasChanged = true;
	}

	float b = one.GetPos().x - one.size.x - two.GetPos().x + two.size.x;
	if (abs(b) < overlap_size)
	{
		overlap = { 0,0,0 };
		overlap_size = b;
		overlap.x = b;
		hasChanged = true;
	}

	float c = one.GetPos().y + one.size.y - two.GetPos().y - two.size.y;
	if (abs(c) < overlap_size)
	{
		overlap = { 0,0,0 };
		overlap_size = c;
		overlap.y = c;
		hasChanged = true;
	}

	float d = one.GetPos().y - one.size.y - two.GetPos().y + two.size.y;
	if (abs(d) < overlap_size)
	{
		overlap = { 0,0,0 };
		overlap_size = d;
		overlap.y = d;
		hasChanged = true;
	}

	return (hasChanged) ? overlap : glm::vec3(0);
}