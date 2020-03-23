#pragma once
#include "PhysicsObject.h"

class GameObject2D : public PhysicsObject
{
public :
	GameObject2D() {};
	~GameObject2D() {};

	struct TwoMesh
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
	};


	void Draw();
	void SetPos(glm::vec3 newPos);
	void SetTexture(Texture* texture);
	void Rotate(float rotation);

	unsigned int	vao, vbo, ibo;
	glm::vec3 color = glm::vec3(1);
	glm::vec2 size = glm::vec2(1, 1);
	glm::vec3 position = glm::vec3(0);
	TwoMesh twoMesh;
	Texture* tex = nullptr;
	glm::mat4 model = glm::mat4(1);
};

