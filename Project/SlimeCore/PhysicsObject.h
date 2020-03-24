#pragma once
#include "glm.hpp"
#include "Mesh.h"
#include "Types.h"
#include "Shader.h"
#include "Material.h"

class PhysicsObject
{
protected:
	PhysicsObject() {}

public:

	void fixedUpdate(glm::vec2 gravity, float timeStep);
	void debug();
	void resetPosition() {};
};

