#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Shader.h"

class Material
{
public:
	Material(Shader* shader = nullptr);
	virtual ~Material();

	Shader* GetShader();

protected:
	Shader* shader = nullptr;
};

