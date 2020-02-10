#pragma once
#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"
#include "ext.hpp"
#include "Primitives.h"
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	Primitives prim;

	void InitialiseQuad();
	virtual void Draw();

protected:
	unsigned int vao, vbo, ibo;
};

