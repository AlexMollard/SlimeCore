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
	void debug();
	void resetPosition() {};
};

