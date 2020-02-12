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


void Mesh::create(Primitives::TYPE type, float argOne, float argTwo, int argThree)
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
		hasIBO = true;
		break;
	case Primitives::Cube:
		prim = Cube::Create();
		hasIBO = true;
		break;
	case Primitives::Cylinder:
		prim = Cylinder::Create(argOne, argTwo, argThree);
		hasIBO = true;
		break;
	case Primitives::Sphere:
		prim = Sphere::Create(argOne, argTwo, argThree);
		hasIBO = true;
		break;
	case Primitives::Torus:
		prim = Torus::Create(argOne, argTwo, argThree, 10);
		hasIBO = true;
		break;
	default:
		break;
	}
	
	std::vector<float> newvertices;

	for (int i = 0; i < prim.vertices.size(); i++)
	{
		// Postitions
		newvertices.push_back(prim.vertices[i].x);
		newvertices.push_back(prim.vertices[i].y);
		newvertices.push_back(prim.vertices[i].z);

		// Normals
		if (prim.normals.size() < 1)
		{
			newvertices.push_back(1);
			newvertices.push_back(1);
			newvertices.push_back(1);
		}
		else
		{
			newvertices.push_back(prim.normals[i].x);
			newvertices.push_back(prim.normals[i].y);
			newvertices.push_back(prim.normals[i].z);
		}

		// UVS
		newvertices.push_back(prim.uvs[i].x);
		newvertices.push_back(prim.uvs[i].y);
	}

	// Fill vertex Buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, newvertices.size() * sizeof(float), newvertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, prim.indices.size() * sizeof(unsigned int), prim.indices.data(), GL_STATIC_DRAW);

	// Enable first element as position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Enable second element as normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Enable third element as UVS
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Unbind buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	// using indices or just vertices?
	if (hasIBO)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glDrawElements(GL_TRIANGLES, prim.indices.size(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glDrawArrays(GL_TRIANGLES, 0, prim.vertices.size());
	}
}	