#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(Shader* shader = nullptr, Texture* = nullptr);
	virtual ~Material();

	Shader* GetShader();
	Texture* GetTexture();

protected:
	Shader* shader = nullptr;
	Texture* texture = nullptr;
	bool hasOwnTexture = false;
};

