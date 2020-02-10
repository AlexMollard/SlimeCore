#include "Mesh.h"

Mesh::Mesh() : vao(0), vbo(0), ibo(0)
{
	glGenVertexArrays(1, &vao);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}


void Mesh::create(Primitives::TYPE type, float radius, float halfLength, int slices)
{
	// Check if mesh is not yet made
	assert(vao != 0);

	// Bind vertex array
	glBindVertexArray(vao);

	// Generate buffers
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glGenVertexArrays(1, &vbo);
	glGenVertexArrays(1, &ibo);

	switch (type)
	{
	case Primitives::Plane:
		prim = Plane::Create();
		break;
	case Primitives::Cube:
		prim = Cube::Create();
		break;
	case Primitives::Cylinder:
		prim = Cylinder::Create(radius, halfLength, slices);
		break;
	case Primitives::Sphere:
		break;
	case Primitives::Cone:
		break;
	default:
		break;
	}

	// Fill vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, prim.vertices.size() * sizeof(glm::vec3), prim.vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, prim.indices.size() * sizeof(unsigned int), prim.indices.data(), GL_STATIC_DRAW);

	// Enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	// Unbind buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	// using indices or just vertices?
	if (ibo != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, prim.indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
		glDrawArrays(GL_TRIANGLES, 0, prim.vertices.size() / 3);
}	