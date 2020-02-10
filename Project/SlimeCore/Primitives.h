#pragma once
#include "glm.hpp"
#include <vector>
class Primitives
{
public:
	enum TYPE 
	{
		Plane,
		Cube,
		Cylinder,
		Tube,
		Sphere,
		Torus,
		Cone
	};

	TYPE type;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};


class Plane : public Primitives
{
	Plane();
};

class Cube : public Primitives
{
	Cube();
};

class Cylinder : public Primitives
{
	Cylinder(float radius, float halfLength, int slices);
public:
	static Primitives Create(float radius, float halfLength, int slices) {
		return Cylinder(radius, halfLength, slices);
	}
};

class Tube : public Primitives
{
	Tube();
};

class Sphere : public Primitives
{
	Sphere();
};

class Torus : public Primitives
{
	Torus();
};

class Cone : public Primitives
{
	Cone();
};



