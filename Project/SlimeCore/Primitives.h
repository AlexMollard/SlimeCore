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
		Sphere,
		Cone
	};

	TYPE type;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
};


class Plane : public Primitives
{
	Plane();
public:
	TYPE type = TYPE::Plane;
	static Primitives Create() {
		return Plane();
	}
};

class Cube : public Primitives
{
	Cube();
public:
	TYPE type = TYPE::Cube;
	static Primitives Create() {
		return Cube();
	}
};

class Cylinder : public Primitives
{
	Cylinder(float radius, float halfLength, int slices);
public:
	TYPE type = TYPE::Cylinder;
	static Primitives Create(float radius, float halfLength, int slices) {
		return Cylinder(radius, halfLength, slices);
	}
};

class Sphere : public Primitives
{
	Sphere();
};

class Cone : public Primitives
{
	Cone();
};



