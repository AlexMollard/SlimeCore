#pragma once
#include "gl_core_4_5.h"
#include "glm.hpp"
#include "glfw3.h"
#include "ext.hpp"
#include "Primitives.h"

struct Vertex
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> uvs;
};

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	Vertex vertexes;
	Primitives prim;
	bool hasIBO = false;
	void create(Primitives::TYPE type = Primitives::TYPE::Cube, float radius = 0.5f, float halfLength = 0.5f, int slices = 10);
	virtual void Draw();

protected:
	unsigned int vao, vbo, ibo;
};

