#include "Primitives.h"

#define PI 3.14159265358979323846264338327950288
#define TWOPI (2.0*3.14159265358979323846264338327950288)

Plane::Plane()
{
	vertices.push_back(glm::vec3(-0.5f, 0, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0, 0.5f));
	vertices.push_back(glm::vec3(-0.5f, 0, -0.5f));

	vertices.push_back(glm::vec3(-0.5f, 0, -0.5f));
	vertices.push_back(glm::vec3(0.5f, 0, 0.5f));
	vertices.push_back(glm::vec3(0.5f, 0, -0.5f));
}

Cube::Cube()
{
	vertices.push_back(glm::vec3(0.5f,  0.5f, -0.5f));  // front top right
	vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));  // front bottom right
	vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));  // front bottom left
	vertices.push_back(glm::vec3(-0.5f, 0.5f, -0.5f));  // front top left 

	vertices.push_back(glm::vec3(0.5f, 0.5f, 0.5f));  // back top right
	vertices.push_back(glm::vec3(0.5f, -0.5f, 0.5f)); // back bottom right
	vertices.push_back(glm::vec3(-0.5f, -0.5f, 0.5f));  // back bottom left
	vertices.push_back(glm::vec3(-0.5f, 0.5f, 0.5f));   // back top left 

	unsigned int cubeIndices[] =
	{
		0, 1, 3,   // front first triangle
		1, 2, 3,   // front second triangle

		4, 5, 7,   // back first triangle
		5, 6, 7,   // back second triangle

		4, 5, 1,   // right first triangle
		1, 0, 4,   // right second triangle

		3, 2, 6,   // left first triangle
		6, 7, 3,   // left second triangle

		0, 3, 7,   // top first triangle
		7, 4, 0,   // top second triangle

		1, 2, 6,   // bottom first triangle
		6, 5, 1    // bottom second triangle
	};

	int length = sizeof(cubeIndices) / sizeof(unsigned int);

	indices = std::vector<unsigned int>(cubeIndices, cubeIndices + length);
}

Cylinder::Cylinder(float radius, float halfLength, int slices)
{
	vertices.push_back(glm::vec3(0.0f, halfLength, 0.0f));
	vertices.push_back(glm::vec3(0.0f, -halfLength, 0.0f));

	for (int i = 0; i < slices; i++)
	{
		float theta = TWOPI * ((float)i / slices);

		vertices.push_back(glm::vec3(radius * glm::cos(theta), halfLength, radius * glm::sin(theta)));
		vertices.push_back(glm::vec3(radius * glm::cos(theta), -halfLength, radius * glm::sin(theta)));
	}

	for (int i = 2; i < vertices.size() - 2; i += 2)
	{
		indices.push_back(i + 2);
		indices.push_back(i);
		indices.push_back(0);

		indices.push_back(i + 3);
		indices.push_back(1);
		indices.push_back(i + 1);

		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+1);

		indices.push_back(i+2);
		indices.push_back(i+3);
		indices.push_back(i+1);
	}

	indices.push_back(2);
	indices.push_back(vertices.size() - 2);
	indices.push_back(0);

	indices.push_back(1);
	indices.push_back(vertices.size() - 1);
	indices.push_back(3);

	indices.push_back(vertices.size() - 2);
	indices.push_back(2);
	indices.push_back(vertices.size() - 1);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(vertices.size() - 1);

}

Tube::Tube()
{

}

Sphere::Sphere()
{

}


Torus::Torus()
{

}

Cone::Cone()
{

}