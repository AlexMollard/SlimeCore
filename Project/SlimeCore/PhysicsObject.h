#pragma once
#include "glm.hpp"
#include "Types.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"

class PhysicsObject
{
protected:
	PhysicsObject() {}

public:
	void debug();
	void resetPosition() {};
};
