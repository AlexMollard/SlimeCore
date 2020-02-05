#pragma once
#include "glm.hpp"
#include "ext.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
class Application3D
{
public:
	Application3D();
	virtual ~Application3D();

	virtual bool StartUp();
	virtual bool ShutDown();

	virtual void Update(float deltaTime);
	virtual void Draw();
protected:
	// MPV
	glm::mat4 model;
	glm::mat4 projection;
};

